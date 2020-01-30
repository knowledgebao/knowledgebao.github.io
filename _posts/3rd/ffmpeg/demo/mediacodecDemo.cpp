extern "C" {
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/buffer.h>
#include <libavutil/error.h>
#include <libavutil/hwcontext.h>
#include <libavutil/imgutils.h>
#include <libavutil/mem.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
#include <libavutil/time.h>
#include <libswscale/swscale.h>
#include <libavcodec/jni.h>
}

inline int test(void *vm) {
    AVDictionary *avFormatOptions = NULL;
    AVDictionary *avCodecOptions = NULL;
    int err, i, videoStreamId;
    AVDictionaryEntry *e;
    AVFormatContext *pFormatCtx = NULL;
    AVCodecContext *pCodecCtx = NULL;
    AVCodec *pCodec = NULL;
    AVFrame *pFrame = NULL;
    AVPacket packet;

    av_jni_set_java_vm(vm, nullptr);

#if LIBAVCODEC_VERSION_MAJOR <= 57
    av_register_all();
    avformat_network_init();
#endif

    if ((err = avformat_open_input(&pFormatCtx, "/sdcard/megsdk/data/binjiangdao.ts", NULL, &avFormatOptions)) != 0) {
        LOG_EF("Couldn't open file. Error code: %d", err);
        return 2;
    }
    //pFormatCtx->flags |= AVFMT_FLAG_KEEP_SIDE_DATA;

    e = NULL;
    while ((e = av_dict_get(avFormatOptions, "", e, AV_DICT_IGNORE_SUFFIX))) {
        LOG_EF("avformat_open_input: option \"%s\" not recognized", e->key);
    }

    if ((err = avformat_find_stream_info(pFormatCtx, NULL)) < 0) {
        LOG_EF("Couldn't find stream information. Error code: %d", err);
        return 3;
    }

    videoStreamId = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamId = i;
            break;
        }
    }

    if (videoStreamId == -1) {
        LOG_EF("Can't find video stream");
        return 4;
    }

    //pCodec = avcodec_find_decoder(pFormatCtx->streams[videoStreamId]->codec->codec_id);
    pCodec = avcodec_find_decoder_by_name("h264_mediacodec"); //HW acceleration works only if codec is selected manually
    if (pCodec == NULL) {
        LOG_EF("Can't find codec for input stream");
        return 6;
    }
    LOG_EF("Codec: %s", pCodec->name);

    pCodecCtx = avcodec_alloc_context3(pCodec); //pCodecCtx = pFormatCtx->streams[videoStreamId]->codec;
    avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStreamId]->codecpar);
    LOG_IF("decoder pix_fmt = %s.", av_get_pix_fmt_name(pCodecCtx->pix_fmt));

    //av_dict_set(&avCodecOptions, "delay_flush", "1", 0);
    if ((err = avcodec_open2(pCodecCtx, pCodec, &avCodecOptions)) < 0) {
        LOG_EF("Can't open codec. Error code: %d", err);
        return 7;
    }

    e = NULL;
    while ((e = av_dict_get(avCodecOptions, "", e, AV_DICT_IGNORE_SUFFIX))) {
        LOG_EF("avcodec_open2: option \"%s\" not recognized", e->key);
    }

    //Allocate video frame YUV and RGB
    pFrame = av_frame_alloc();
    if (pFrame == NULL) {
        LOG_EF("Can't alloc memory for video frames");
        return 8;
    }

    LOG_EF("Initialized. Entering main loop...");

    i = 1;
    int j = 1;
    while (av_read_frame(pFormatCtx, &packet) >= 0) {
        //Is this a packet from the video stream?
        if (packet.stream_index == videoStreamId) {
            //Decode video frame
            auto start = std::chrono::high_resolution_clock::now();
            err = avcodec_send_packet(pCodecCtx, &packet);
            while (err == -11) {
                std::this_thread::sleep_for(std::chrono::microseconds(1)); //1微秒
                err = avcodec_receive_frame(pCodecCtx, pFrame);
                err = avcodec_send_packet(pCodecCtx, &packet);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                if (elapsed.count() > 100) {
                    LOG_EF("**************************break,cost = %d", (int)elapsed.count());
                    break;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;

            LOG_EF("+++send err = %d(%d), cost: %d ms", err, i, (int)elapsed.count());

            while (err >= 0) {
                err = avcodec_receive_frame(pCodecCtx, pFrame);
                if (err == 0) {
                    // meg_image_raw_t raw;
                    // meg_image_info_t desc;
                    // desc.width = pFrame->width;
                    // desc.height = pFrame->height;
                    // desc.format = MEG_COLOR_GRAY;
                    // raw.create(desc, pFrame->data[0], true);
                    // std::string path = strings::join_path("/sdcard/megsdk/data/output", strings::getname() + ".jpg");
                    // raw.write(path.c_str());
                    LOG_EF("---+++recv err = %d(%d)", err, j++);
                }
                LOG_EF("---recv err = %d(%d)", err, i);
            };
            i++;
            if (i > 500) {
                //break;
            }
        }

        //Free the packet that was allocated by av_read_frame
        av_packet_unref(&packet);
    }

    LOG_EF("Leaving main loop. Cleanup...");

    // Free the frame
    av_free(pFrame);

    // Close the codec
    avcodec_free_context(&pCodecCtx);

    // Close the video file
    avformat_close_input(&pFormatCtx);

    return 0;
}
# avcodec_send_packet/avcodec_receive_frame

## 简介

`int avcodec_send_packet(AVCodecContext *avctx, const AVPacket *avpkt)`

- 说明
  - 将原始数据包数据作为输入提供给解码器。
  - 在内部，这个调用将复制相关的AVCodecContext字段，这些字段会影响每个包的解码，并在实际解码包时应用它们。(例如AVCodecContext.skip_frame，它可能会指示解码器丢弃使用此函数发送的包所包含的帧。)

- 警告
  - 输入缓冲区avpkt->data 长度必须比实际读取字节多AV_INPUT_BUFFER_PADDING_SIZE，因为一些优化的位流读取器一次读取32位或64位，可以越界。
  - 不要将此API与avcodec_decode_video2()混合使用，它将返回意想不到的结果。

- 注意
  - AVCodecContext必须使用avcodec_open2()打开，然后才能将数据包提供给解码器。

- 参数
  - avctx： codec context
  - [in] avpkt：输入 AVPacket. 通常，这将是一个单独的视频帧，或几个完整的音频帧。数据包的所有权仍然属于调用者，而解码器不会写入数据包。解码器可以创建对包数据的引用(如果包没有被引用计数，则复制它)。与以前的api不同，包总是被完全使用，如果它包含多个帧(例如一些音频编解码器)，那么在发送新包之前需要多次调用avcodec_receive_frame()。它可以是空的(或AVPacket的数据集为空，大小设为0);在这种情况下，它被认为是一个刷新包，它表示流的结束。发送第一个刷新包将返回成功，多次发送是不必要的，并将返回AVERROR_EOF。如果解码器仍然有缓冲帧，它将在发送一个刷新包后返回它们。

- 返回值
  - 0表示成功
  - AVERROR(EAGAIN):当前状态下不接受输入，用户必须使用avcodec_receive_frame()读取输出(读取所有输出后，应该重新发送数据包，EAGAIN调用不会失败)。
  - AVERROR_EOF:解码器被刷新,不允许发送新包。(多次发送刷新包也会返回此错误)
  - AVERROR (EINVAL):无效参数，比如是编解码器，或者其他错误
  - AVERROR (ENOMEM):未能添加到内部队列
  - 其他错误

`int avcodec_receive_frame(AVCodecContext *avctx, AVFrame *frame)`

- 说明
  - 从解码器返回解码后的输出数据。
- 参数
  - avctx： codec context
  - frame： 这将被设置为由解码器分配的视频或音频帧(取决于解码器的类型)，内部调用av_frame_unref(frame)重置frame
- 返回值
  - 0: 成功
  - AVERROR(EAGAIN): 需要更多解码数据
  - AVERROR_EOF: 结束
  - AVERROR(EINVAL): 打开失败
  - AVERROR_INPUT_CHANGED: 当设置 AV_CODEC_FLAG_DROPCHANGED 参数后，此返回表示原始数据参数发生了变化。
  - other: legitimate decoding errors

## 相关源码

```C++
int avcodec_send_packet(AVCodecContext *avctx, const AVPacket *avpkt)
{
    AVCodecInternal *avci = avctx->internal;
    int ret;

    if (!avcodec_is_open(avctx) || !av_codec_is_decoder(avctx->codec))
        return AVERROR(EINVAL);

    if (avctx->internal->draining)
        return AVERROR_EOF;

    if (avpkt && !avpkt->size && avpkt->data)
        return AVERROR(EINVAL);

    av_packet_unref(avci->buffer_pkt);
    if (avpkt && (avpkt->data || avpkt->side_data_elems)) {
        ret = av_packet_ref(avci->buffer_pkt, avpkt);
        if (ret < 0)
            return ret;
    }

    ret = av_bsf_send_packet(avci->filter.bsfs[0], avci->buffer_pkt);
    if (ret < 0) {
        av_packet_unref(avci->buffer_pkt);
        return ret;
    }

    if (!avci->buffer_frame->buf[0]) {
        ret = decode_receive_frame_internal(avctx, avci->buffer_frame);
        if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
            return ret;
    }

    return 0;
}
int avcodec_receive_frame(AVCodecContext *avctx, AVFrame *frame)
{
    AVCodecInternal *avci = avctx->internal;
    int ret;

    av_frame_unref(frame);

    if (!avcodec_is_open(avctx) || !av_codec_is_decoder(avctx->codec))
        return AVERROR(EINVAL);

    if (avci->buffer_frame->buf[0]) {
        av_frame_move_ref(frame, avci->buffer_frame);
    } else {
        ret = decode_receive_frame_internal(avctx, frame);
        if (ret < 0)
            return ret;
    }

    if (avctx->codec_type == AVMEDIA_TYPE_VIDEO) {
        ret = apply_cropping(avctx, frame);
        if (ret < 0) {
            av_frame_unref(frame);
            return ret;
        }
    }

    avctx->frame_number++;

    return 0;
}
```

Demo

```C++
static void decode(AVCodecContext *dec_ctx, AVFrame *frame, AVPacket *pkt)
{
    int ret;
    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        exit(1);
    }else if (ret == AVERROR(EAGAIN)){
        recv(dec_ctx, frame);
        ret = avcodec_send_packet(dec_ctx, pkt);
    }
    if (ret >= 0) {
        recv(dec_ctx, frame);
    }
}

static void recv(AVCodecContext *dec_ctx, AVFrame *frame)
{
    int ret;
    do {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during decoding\n");
            exit(1);
        }

        printf("saving frame %3d\n", dec_ctx->frame_number);
    }while (ret >= 0);
}

```

## 参考资料

1. [FFmpeg源码分析](https://www.jianshu.com/p/82784951d5b2)

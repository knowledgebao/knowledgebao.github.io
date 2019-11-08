---
layout: post
title: ffmpeg_timebase
date: 2019-11-01 10:13:58
description: ffmpeg_timebase
tag: ffmpeg

---


# time_base
AVRational time_base
```
/**
 * @defgroup lavu_math_rational AVRational
 * @ingroup lavu_math
 * Rational number calculation.
 *
 * While rational numbers can be expressed as floating-point numbers, the
 * conversion process is a lossy one, so are floating-point operations. On the
 * other hand, the nature of FFmpeg demands highly accurate calculation of
 * timestamps. This set of rational number utilities serves as a generic
 * interface for manipulating rational numbers as pairs of numerators and
 * denominators.
 *
 * Many of the functions that operate on AVRational's have the suffix `_q`, in
 * reference to the mathematical symbol "ℚ" (Q) which denotes the set of all
 * rational numbers.
 *
 * @{
 */

/**
 * Rational number (pair of numerator and denominator).
 */
typedef struct AVRational{
    int num; ///< Numerator
    int den; ///< Denominator
} AVRational;
```
+ AVStream->time_base单位为秒,AVStream->time_base为1/90000
+ AVCodecContext->time_base单位为秒,AVCodecContext->time_base为1/30(假设frame_rate为30)

##AVPacket:
pts,dts:AVStream->time_base为单位
##AVFrame:
pkt_pts,pkt_dts:AVStream->time_base为单位
pts:AVCodecContext->time_base
##InputStream:
pts,dts:AV_TIME_BASE为单位(微秒)  #define AV_TIME_BASE   1000000
##OutputStream

##转换函数
av_rescale_q(a,b,c)作用相当于执行a*b/c
1. InputStream(AV_TIME_BASE)到AVPacket(AVStream->time_base)
 pkt->dts = av_rescale_q(inputStream->dts, AV_TIME_BASE_Q, AVStream->time_base); 
 pkt->dts = inputStream->dts*AV_TIME_BASE_Q/AVStream->time_base;
 
2. AVPacket(AVStream->time_base)到InputStream(AV_TIME_BASE)
 inputStream->dts = av_rescale_q(pkt->dts, AVStream->time_base, AV_TIME_BASE_Q); 
 inputStream->dts = pkt->dts * AVStream->time_base / AV_TIME_BASE_Q

##后记
AVFrame->pts和AVPacket->pts、AVPacket->dts的值，在解码/编码后，会经历短暂的time_base不匹配的情况：
解码后，decoded_frame->pts的值使用AVStream->time_base为单位，后在AVFilter里面转换成以AVCodecContext->time_base为单位。   //FIXME
编码后，pkt.pts、pkt.dts使用AVCodecContext->time_base为单位，后通过调用"av_packet_rescale_ts"转换为AVStream->time_base为单位。
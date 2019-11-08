---
layout: post
title: ffmpeg-cuda随记
date: 2019-11-01 10:13:58
description: ffmpeg-cuda随记
tag: ffmpeg

---


涉及文件：


涉及结构体及简单关系描述：
AVHWDeviceContext: 具体硬件设备相关结构体
AVFrame:YUV数据存储结构体，如果涉及GPU，hw_frames_ctx指向AVHWFramesContext相关内容。
AVHWFramesContext:被AVFrame引用，内含AVHWDeviceContext引用。
AVCodecContext:编解码的上下文
AVCodec:编解码的结构体,如果是硬编解码，



1, AVFrame:存放yuv相关数据的结构体
data(uint8_t *[AV_NUM_DATA_POINTERS]) :		存放surface(显存)数据
hw_frames_ctx(AVBufferRef *):				AVHWFramesContext 的引用

2, AVHWFramesContext:
关于gpu模式下，AVFrame的描述,一般赋值给AVFrame.hw_frames_ctx
av_class(const AVClass *)：				日志相关类
internal(AVHWFramesInternal *)			硬件相关信息，具体详见 AVHWFramesInternal 说明			
device_ref(AVBufferRef *)				指向 AVHWDeviceContext 引用
device_ctx(AVHWDeviceContext *)			device_ref->data,表示AVHWDeviceContext
hwctx(void *)							自身句柄
pool(AVBufferPool *)					frame pool,frames are allocated by av_hwframe_get_buffer().
initial_pool_size(int)					frame pool size
format(enum AVPixelFormat)				surface类型，比如AV_PIX_FMT_CUDA，AV_PIX_FMT_D3D11VA_VLD等		
sw_format(enum AVPixelFormat)			数据格式，比如AV_PIX_FMT_NV12、AV_PIX_FMT_BGR等			
width(int)								宽
height(int)								高
void(* 	free )(struct AVHWFramesContext *ctx)
user_opaque(void *)

AVHWFramesInternal: hw_type(const HWContextType):	各种长度以及硬件结构长度，具体详见 HWContextType 。
					priv(void *):					私有数据
					pool_internal(AVBufferPool *):	
					source_frames(AVBufferRef *):	
					source_allocation_map_flags(int):

3, AVHWDeviceContext:
设备结构体，不同硬件设备含义不同。
此结构可以通过 av_hwdevice_ctx_alloc() 创建一个引用 AVBufferRef*,AVBufferRef->data指向AVHWDeviceContext
当所有指向AVHWDeviceContext的应用被销毁后，AVHWDeviceContext会自毁，当然也可以通过回掉通知调用者
av_class(const AVClass *)：				日志相关类
internal(AVHWDeviceInternal *)：		硬件相关信息，具体详见 AVHWDeviceInternal 说明
type(enum AVHWDeviceType):				硬件类型AV_HWDEVICE_TYPE_CUDA/AV_HWDEVICE_TYPE_OPENCL等	
hwctx(void*):							自身句柄，和internal->source_devide的区别是啥？
void(*free)(struct AVHWDeviceContext *ctx)删除AVHWDeviceContext触发的回调
user_opaque(void *):					user数据												
	
相关结构体	
AVHWDeviceInternal: hw_type(const HWContextType):	各种长度以及硬件结构长度，具体详见 HWContextType 。
					priv(void *):					私有数据
					source_device(AVBufferRef *):	指向 AVHWDeviceContext 的引用

4, AVCodecContext:
hwaccel(const struct AVHWAccel *):
hwaccel_context(void *):
hw_frames_ctx(AVBufferRef *):
hw_device_ctx(AVBufferRef *):
hwaccel_flags(int):
extra_hw_frames(int):

5, AVCodec:
hw_configs(const struct AVCodecHWConfigInternal **):

其它：
1>, AVBufferRef:
buffer(AVBuffer):
data(uint8_t*):
size(int);

2>, AVBuffer(通用结构体,可被引用):
data(uint8_t *)				:数据
size(int)					:大小
refcount(atomic_uint)		:被引用次数
opaque(void *)				:用户数据
flags(int)					:标志，类似BUFFER_FLAG_*
void(* 	free )(void *opaque, uint8_t *data):释放时触发的回调
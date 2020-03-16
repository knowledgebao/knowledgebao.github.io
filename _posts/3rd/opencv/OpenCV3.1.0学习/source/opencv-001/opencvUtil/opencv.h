#pragma once

#include "ssn.h"

SSN_API_BEGIN

enum {
    GrayScaleCV = 0,
    // YYYY... U... V...
    I420ScaleCV = 1,
    BGRScaleCV = 2,
    YBGRScaleCV = 3,
    YUVScaleCV = 4,
    // YYYY... UV...
    NV12ScaleCV = 5,
};

typedef struct SSNImage *SSNImageHandle;
void SSNImageRelease(SSNImageHandle handle);
void SSNImageGetInfo(SSNImageHandle handle, int *width, int *height, int *step);
void SSNImageGetData(SSNImageHandle handle, void **data, int *size);

typedef struct SSNBuffer *SSNBufferHandle;
void SSNBufferRelease(SSNBufferHandle handle);
void SSNBufferGetData(SSNBufferHandle handle, void **data, int *size);

SSNBufferHandle SSNImageEncode(int offset, int width, int height, int step, int scale, const void *data, bool png);

// gray,bgr
SSNImageHandle SSNImageRead(const void *str, bool color, int *width, int *height);
SSNImageHandle SSNImageDecode(const void *str, int len, bool color, int *width, int *height);
SSNImageHandle SSNImageResize(int width, int height, int step, int scale, const void *data, int destWidth,
                              int destHeight);

SSNImageHandle GrayToBGR(int offset, int width, int height, int stride, const void *data);
SSNImageHandle BGRToGray(int offset, int width, int height, int stride, const void *data);
SSNImageHandle BGRToI420(int offset, int width, int height, int stride, const void *data);
SSNImageHandle I420ToBGR(int width, int height, const void *data);

// v3 reduce some parameter.
typedef struct ImageInfo {
    int scale;
    int width;
    int height;
    int stride;
    uintptr_t data;
} ImageInfo;

typedef struct ImageRect {
    int left, top, width, height;
} ImageRect;

void BGRDrawI420_V1(void *canvas, ImageInfo cinfo, const void *img, ImageInfo iinfo, ImageRect rect);
void BGRDrawI420_V2(void *canvas, ImageInfo cinfo, const void *img, ImageInfo iinfo, ImageRect rect);
void BGRDrawI420_V3(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth);
void BGRDrawNV12(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth);

void BGRDrawBGR(void *canvas, ImageInfo cinfo, const void *img, ImageInfo iinfo, ImageRect rect);
void BGRDrawRect(void *canvas, ImageInfo cinfo, ImageRect rect, int color, bool fill);

void YUVDrawYU12(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth);
void YUVDrawNV12(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth);
void YUVDrawBGR(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth);

void NV12Draw(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth);

void YU12Resize(const void *src, int swidth, int sheight, void *dest, int dwidth, int dheight);
void ImageResize(ImageInfo src, ImageInfo dest, bool smooth);
void ImageWrite(const char *filename, ImageInfo img);

bool HaveOpenCL();

/// yuv src and all dst are not support alignment.
enum {
    CVT_I420ToBGR = 0,
    CVT_NV12ToBGR = 1,
    CVT_GrayToBGR = 2,
    CVT_YUVToBGR = 3,
    CVT_YUVToGray = 4,
    CVT_YUVToI420 = 5,
    CVT_YUVToNV12 = 6,

    CVT_BGRToI420 = 8,
    CVT_BGRToGray = 9,
    CVT_BGRToYUV = 10,

    CVT_YUVToNV12_I420 = 11,
};
void convertColor(const void *src, void *dst, int width, int height, int stride, int code, bool accel);

SSN_API_END

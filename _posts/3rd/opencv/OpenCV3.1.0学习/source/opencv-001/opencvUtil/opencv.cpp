#include "opencv.h"

#include <opencv2/core/version.hpp>
#if CV_MAJOR_VERSION < 3
#include <opencv2/highgui/highgui.hpp>
#else
#include <opencv2/imgcodecs/imgcodecs.hpp>
#endif
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void resizeMat(cv::InputArray src, cv::OutputArray &dst, cv::Size size) {
    int inter = src.getSz().area() > size.area() ? cv::INTER_LINEAR : cv::INTER_AREA;
    cv::resize(src, dst, size, 0, 0, inter);
}

//lines resize
void resizeMat2(cv::Mat &src, cv::Mat &dst, cv::Size size) {
    float rowstep = float(src.rows) / float(size.height);
    float colstep = float(src.cols) / float(size.width);
    if (dst.type() == CV_8UC1) {
        uchar *d = nullptr;
        uchar *s = nullptr;
        for (int i = 0; i < dst.rows; ++i) {
            d = dst.ptr<uchar>(i);
            if (i * rowstep < src.rows) {
                s = src.ptr<uchar>(i * rowstep);
            }
            for (int j = 0; j < dst.cols; ++j) {
                if (j * colstep < src.cols) {
                    d[j] = s[int(j * colstep)]; //Y
                }
            }
        }
    } else if (dst.type() == CV_8UC2) {
        cv::Vec2b *d = nullptr;
        cv::Vec2b *s = nullptr;
        for (int i = 0; i < dst.rows; ++i) {
            d = dst.ptr<cv::Vec2b>(i);
            if (i * rowstep < src.rows) {
                s = src.ptr<cv::Vec2b>(i * rowstep);
            }
            for (int j = 0; j < dst.cols; ++j) {
                if (j * colstep < src.cols) {
                    d[j][0] = s[int(j * colstep)][0]; //U
                    d[j][1] = s[int(j * colstep)][1]; //V
                }
            }
        }
    }
}

//draw planar channel to packet channel(now only support two channel),for example:i420->nv12
void resizeMat3(cv::Mat &src, cv::Mat &dst, cv::Size size) {
    float rowstep = float(src.rows) / float(size.height);
    float colstep = float(src.cols) / float(size.width);
    if (dst.type() == CV_8UC2) {
        cv::Vec2b *d = nullptr;
        uchar *s0 = nullptr;
        uchar *s1 = nullptr;
        for (int i = 0; i < dst.rows; ++i) {
            d = dst.ptr<cv::Vec2b>(i);
            if (i * rowstep < src.rows) {
                s0 = src.ptr<uchar>(i * rowstep);
            }
            if (i * rowstep < src.rows) {
                s1 = src.ptr<uchar>(i * rowstep + src.rows * src.cols);
            }

            for (int j = 0; j < dst.cols; ++j) {
                if (j * colstep < src.cols) {
                    d[j][0] = s0[int(j * colstep)]; //U
                    d[j][1] = s1[int(j * colstep)]; //V
                }
            }
        }
    }
}

void resizeMat(cv::InputArray src, cv::OutputArray dst, int width, int height) {
    cv::resize(src, dst, cv::Size(width, height));
}
void resizeMat(cv::InputArray src, cv::OutputArray dst) {
    cv::resize(src, dst, dst.size());
}
/////////////////////////////////////////

typedef struct SSNImage {
    cv::Mat mat;
} * SSNImageHandle;

void SSNImageRelease(SSNImageHandle handle) {
    // handle->mat = cv::Scalar(0);
    delete handle;
}

void SSNImageGetInfo(SSNImageHandle handle, int *width, int *height,
                     int *step) {
    assert(handle != NULL);
    const cv::Mat &mat = handle->mat;
    *width = mat.cols;
    *height = mat.rows;
    *step = mat.step[0];
}

void SSNImageGetData(SSNImageHandle handle, void **data, int *size) {
    assert(handle != NULL);
    const cv::Mat &mat = handle->mat;
    *size = mat.step[0] * mat.rows;
    *data = mat.data;
}

// @width int IN: limit width, OUT: raw width.
// @height int IN: limit height, OUT: raw height.
void imageShrink(SSNImageHandle handle, int *width, int *height) {
    assert(handle != NULL);
    if (width == NULL || height == NULL) {
        return;
    }

    cv::Mat img = handle->mat;
    int destWidth = *width;
    int destHeight = *height;
    if (img.cols > destWidth || img.rows > destHeight) {
        double sx = destWidth / double(img.cols);
        double sy = destHeight / double(img.rows);
        if (sx < sy) {
            destHeight = int(img.rows * sx + 0.5);
        } else {
            destWidth = int(img.cols * sy + 0.5);
        }
        resizeMat(img, handle->mat, destWidth, destHeight);
    }
    *width = img.cols;
    *height = img.rows;
}

SSNImageHandle SSNImageRead(const void *str, bool color, int *width,
                            int *height) {
    SSNImageHandle handle = new SSNImage();
    handle->mat = cv::imread((const char *)str,
                             color ? cv::IMREAD_COLOR : cv::IMREAD_GRAYSCALE);
    if (handle->mat.empty()) {
        delete handle;
        handle = NULL;
    } else {
        imageShrink(handle, width, height);
    }
    return handle;
}

//如果文件超过一定大小,需要cv::imdecode需要调用temp()函数,需要管理员权限
SSNImageHandle SSNImageDecode(const void *str, int len, bool color, int *width,
                              int *height) {
    SSNImageHandle handle = new SSNImage();
    handle->mat = cv::imdecode(cv::Mat(1, len, CV_8UC1, (void *)str),
                               color ? cv::IMREAD_COLOR : cv::IMREAD_GRAYSCALE);
    if (handle->mat.empty()) {
        delete handle;
        handle = NULL;
    } else {
        imageShrink(handle, width, height);
    }
    return handle;
}

SSNImageHandle SSNImageResize(int width, int height, int step, int scale,
                              const void *data, int destWidth, int destHeight) {
    int type = scale == BGRScaleCV ? CV_8UC3 : CV_8UC1;
    SSNImageHandle handle = new SSNImage();
    resizeMat(cv::Mat(height, width, type, (void *)data, step), handle->mat, destWidth, destHeight);
    return handle;
}

SSNImageHandle GrayToBGR(int offset, int width, int height, int stride,
                         const void *data) {
    SSNImageHandle handle = new SSNImage();
    cv::cvtColor(
        cv::Mat(height, width, CV_8UC1, ((char *)data) + offset, stride),
        handle->mat, cv::COLOR_GRAY2BGR);
    return handle;
}

SSNImageHandle BGRToGray(int offset, int width, int height, int stride,
                         const void *data) {
    SSNImageHandle handle = new SSNImage();
    cv::cvtColor(
        cv::Mat(height, width, CV_8UC3, ((char *)data) + offset, stride),
        handle->mat, cv::COLOR_BGR2GRAY);
    return handle;
}
SSNImageHandle BGRToI420(int offset, int width, int height, int stride,
                         const void *data) {
    SSNImageHandle handle = new SSNImage();
    cv::cvtColor(
        cv::Mat(height, width, CV_8UC3, ((char *)data) + offset, stride),
        handle->mat, cv::COLOR_RGB2YUV_I420);
    return handle;
}
SSNImageHandle I420ToBGR(int width, int height, const void *data) {
    SSNImageHandle handle = new SSNImage();
    cv::cvtColor(cv::Mat(height + height / 2, width, CV_8UC1, (char *)data),
                 handle->mat, cv::COLOR_YUV2RGB_I420);
    return handle;
}
/////////////////////////////////////////

typedef struct SSNBuffer {
    std::vector<unsigned char> buf;
} * SSNBufferHandle;

void SSNBufferRelease(SSNBufferHandle handle) {
    // handle->buf[0] = 0;
    delete handle;
}

void SSNBufferGetData(SSNBufferHandle handle, void **data, int *size) {
    assert(handle != NULL);
    *size = int(handle->buf.size());
    *data = handle->buf.data();
}

SSNBufferHandle SSNImageEncode(int offset, int width, int height, int step,
                               int scale, const void *data, bool png) {
    cv::Mat image;
    if (scale == I420ScaleCV) {
        assert(offset == 0);
        assert(step == 0 || step == width);
        cv::cvtColor(cv::Mat(height + height / 2, width, CV_8UC1, (void *)data),
                     image, cv::COLOR_YUV420p2RGB);
    } else {
        int type = scale == BGRScaleCV ? CV_8UC3 : CV_8UC1;
        image = cv::Mat(height, width, type, ((char *)data) + offset, step);
    }
    SSNBufferHandle handle = new SSNBuffer();
    cv::imencode(png ? ".png" : ".jpg", image, handle->buf); // quality 95
    return handle;
}

/////////////////////////////////////////

inline int ToInter(bool smooth) {
    return smooth ? cv::INTER_CUBIC : cv::INTER_LINEAR;
}

inline cv::Rect ToRect(ImageRect rect) {
    return cv::Rect(rect.left, rect.top, rect.width, rect.height);
}

inline cv::Size GetSize(ImageRect rect) {
    return cv::Size(rect.width, rect.height);
}

cv::Mat ToMat(ImageInfo info) {
    char *ptr = reinterpret_cast<char *>(info.data);
    switch (info.scale) {
    case GrayScaleCV:
        return cv::Mat(info.height, info.width, CV_8UC1, ptr, info.stride);
    case I420ScaleCV:
    case NV12ScaleCV:
        return cv::Mat(info.height + info.height / 2, info.width, CV_8UC1, ptr);
    case BGRScaleCV:
    case YUVScaleCV:
        return cv::Mat(info.height, info.width, CV_8UC3, ptr, info.stride);
    default:
        SSN_LOGF("bad scale %d", info.scale);
        assert(false);
    }
    return cv::Mat();
}

inline cv::Mat ToMat(ImageInfo info, ImageRect rect) {
    return ToMat(info)(ToRect(rect));
}

void BGRDrawI420_V1(void *canvas, ImageInfo cinfo, const void *img,
                    ImageInfo iinfo, ImageRect rect) {
    cv::Mat tmp(iinfo.height, iinfo.width, CV_8UC3);
    cv::Mat out(cinfo.height, cinfo.width, CV_8UC3, (char *)canvas,
                cinfo.stride);
    cv::Mat src(iinfo.height + iinfo.height / 2, iinfo.width, CV_8UC1,
                (char *)img);
    cv::Rect rc(rect.left, rect.top, rect.width, rect.height);
    cv::cvtColor(src, tmp, cv::COLOR_YUV2RGB_I420);
    resizeMat(tmp, out(rc), rc.width, rc.height);
}

void BGRDrawI420_V2(void *canvas, ImageInfo cinfo, const void *img,
                    ImageInfo iinfo, ImageRect rect) {
    cv::Mat tmp(rect.height + rect.height / 2, rect.width, CV_8UC1);
    cv::Mat src(iinfo.height + iinfo.height / 2, iinfo.width, CV_8UC1,
                (char *)img);
    YU12Resize(img, iinfo.width, iinfo.height, tmp.data, rect.width,
               rect.height);

    cv::Mat out(cinfo.height, cinfo.width, CV_8UC3, (char *)canvas,
                cinfo.stride);
    cv::Rect rc(rect.left, rect.top, rect.width, rect.height);
    cv::cvtColor(tmp, out(rc), cv::COLOR_YUV2RGB_I420);
}

const cv::Mat MakeHalfYUV_YU12(char *img, ImageInfo info) {
    cv::Size half(info.width / 2, info.height / 2);
    cv::Mat yuv(half, CV_8UC3);

    cv::Mat y(half, CV_8UC1);
    resizeMat(cv::Mat(info.height, info.width, CV_8UC1, img), y, half);
    cv::insertChannel(y, yuv, 0);

    img += info.height * info.width;
    cv::insertChannel(cv::Mat(half, CV_8UC1, img), yuv, 1);

    img += (info.height / 2) * (info.width / 2);
    cv::insertChannel(cv::Mat(half, CV_8UC1, img), yuv, 2);
    return yuv;
}

const cv::Mat MakeHalfYUV_NV12(char *img, ImageInfo info) {
    cv::Size half(info.width / 2, info.height / 2);
    cv::Mat yuv(half, CV_8UC3);
    cv::Mat y(half, CV_8UC1);
    resizeMat(cv::Mat(info.height, info.width, CV_8UC1, img), y, half);
    cv::insertChannel(y, yuv, 0);

    img += info.height * info.width;
    cv::Mat vu(info.height / 2, info.width / 2, CV_8UC2, img);
    cv::extractChannel(vu, y, 0);
    cv::insertChannel(y, yuv, 1);

    cv::extractChannel(vu, y, 1);
    cv::insertChannel(y, yuv, 2);
    return yuv;
}

void BGRDrawI420_V3(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth) {
    cv::Mat out = ToMat(canvas, rect);
    cv::Mat tmp(out.size(), CV_8UC3);
    resizeMat(MakeHalfYUV_YU12((char *)img.data, img), tmp, out.size());
    cv::cvtColor(tmp, out, cv::COLOR_YUV2BGR);
}

void BGRDrawNV12(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth) {
    cv::Mat out = ToMat(canvas, rect);
    cv::Mat tmp(out.size(), CV_8UC3);
    resizeMat(MakeHalfYUV_NV12((char *)img.data, img), tmp, out.size());
    cv::cvtColor(tmp, out, cv::COLOR_YUV2BGR);
}

void BGRDrawBGR(void *canvas, ImageInfo cinfo, const void *img, ImageInfo iinfo, ImageRect rect) {
    cv::Mat src(iinfo.height, iinfo.width, CV_8UC3, (char *)img, iinfo.stride);
    cv::Mat out(cinfo.height, cinfo.width, CV_8UC3, (char *)canvas, cinfo.stride);
    cv::Rect rc(rect.left, rect.top, rect.width, rect.height);
    resizeMat(src, out(rc));
}

void BGRDrawRect(void *canvas, ImageInfo cinfo, ImageRect rect, int color,
                 bool fill) {
    cv::Mat mat(cinfo.height, cinfo.width, CV_8UC3, (char *)canvas,
                cinfo.stride);
    cv::Rect rc(rect.left, rect.top, rect.width, rect.height);
    cv::Scalar s(color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF);
    cv::rectangle(mat, rc, s, fill ? cv::FILLED : 1, cv::LINE_4);
}

void YU12Resize(const void *src, int sw, int sh, void *dest, int dw, int dh) {
    // Y
    resizeMat(cv::Mat(sh, sw, CV_8UC1, (char *)src), cv::Mat(dh, dw, CV_8UC1, (char *)dest));
    // U
    resizeMat(cv::Mat(sh / 2, sw / 2, CV_8UC1, (char *)src + sh * sw),
              cv::Mat(dh / 2, dw / 2, CV_8UC1, (char *)dest + dh * dw));
    // V
    resizeMat(cv::Mat(sh / 2, sw / 2, CV_8UC1,
                      (char *)src + sh * sw + (sh / 2) * (sw / 2)),
              cv::Mat(dh / 2, dw / 2, CV_8UC1,
                      (char *)dest + dh * dw + (dh / 2) * (dw / 2)));
}

void ImageResize(ImageInfo src, ImageInfo dest, bool smooth) {
    assert(src.scale == dest.scale);
    assert(src.scale == GrayScaleCV || src.scale == BGRScaleCV);
    resizeMat(ToMat(src), ToMat(dest));
}

void YUVDrawYU12(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth) {
    cv::Mat yuv = MakeHalfYUV_YU12((char *)img.data, img);
    resizeMat(yuv, ToMat(canvas, rect), GetSize(rect));
}

void YUVDrawNV12(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth) {
    cv::Mat yuv = MakeHalfYUV_NV12((char *)img.data, img);
    resizeMat(yuv, ToMat(canvas, rect), GetSize(rect));
}

void YUVDrawBGR(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth) {
    cv::Mat temp;
    resizeMat(ToMat(img), temp, GetSize(rect));
    cv::cvtColor(temp, ToMat(canvas, rect), cv::COLOR_BGR2YUV);
}

void NV12Draw(ImageInfo canvas, ImageInfo img, ImageRect rect, bool smooth) {
    //GrayScaleCV:I420ScaleCV:BGRScaleCV:YUVScaleCV:
    if (img.scale == NV12ScaleCV) {
        cv::Mat ySrc = cv::Mat(img.height, img.width, CV_8UC1, reinterpret_cast<char *>(img.data));
        cv::Mat yDst = cv::Mat(canvas.height, canvas.width, CV_8UC1, reinterpret_cast<char *>(canvas.data))(ToRect(rect));
        resizeMat2(ySrc, yDst, cv::Size(rect.width, rect.height));

        cv::Mat uvSrc = cv::Mat(img.height / 2, img.width / 2, CV_8UC2, reinterpret_cast<char *>(img.data) + img.height * img.width);
        cv::Rect uvRect = cv::Rect(rect.left / 2, rect.top / 2, rect.width / 2, rect.height / 2);
        cv::Mat uvDst = cv::Mat(canvas.height / 2, canvas.width / 2, CV_8UC2, reinterpret_cast<char *>(canvas.data) + canvas.height * canvas.width)(uvRect);
        resizeMat2(uvSrc, uvDst, cv::Size(rect.width / 2, rect.height / 2));
    } else if (img.scale == I420ScaleCV) {
        cv::Mat ySrc = cv::Mat(img.height, img.width, CV_8UC1, reinterpret_cast<char *>(img.data));
        cv::Mat yDst = cv::Mat(canvas.height, canvas.width, CV_8UC1, reinterpret_cast<char *>(canvas.data))(ToRect(rect));
        resizeMat2(ySrc, yDst, cv::Size(rect.width, rect.height));

        cv::Mat uvSrc = cv::Mat(img.height / 2, img.width / 2, CV_8UC2, reinterpret_cast<char *>(img.data) + img.height * img.width);
        cv::Rect uvRect = cv::Rect(rect.left / 2, rect.top / 2, rect.width / 2, rect.height / 2);
        cv::Mat uvDst = cv::Mat(canvas.height / 2, canvas.width / 2, CV_8UC2, reinterpret_cast<char *>(canvas.data) + canvas.height * canvas.width)(uvRect);
        resizeMat3(uvSrc, uvDst, cv::Size(rect.width / 2, rect.height / 2));
    } else {
        SSN_LOGF("bad scale %d", img.scale);
        assert(false);
    }
}

void ImageWrite(const char *filename, ImageInfo img) {
    assert(img.scale == BGRScaleCV);
    cv::imwrite(filename, ToMat(img));
}

bool HaveOpenCL() {
    // return cv::ocl::haveOpenCL();
    return true;
}

unsigned char clamp8(int v) {
    return v > 255 ? 255 : v < 0 ? 0 : v;
}

unsigned char avgYUV(int v0, int v1, int v2, int v3) {
    return clamp8((((v0 - 128) + (v1 - 128) + (v2 - 128) + (v3 - 128) + 2) >> 2) + 128);
}

void YUVToI420(unsigned char *src, unsigned char *dst, int width, int height) {
    int hw = width / 2;
    int hh = height / 2;
    unsigned char *y = dst;
    unsigned char *u = dst + width * height;
    unsigned char *v = dst + width * height + hw * hh;
    for (int row = 0; row < hh; row++) {
        unsigned char *s0 = src + width * 3 * row * 2;
        unsigned char *s1 = src + width * 3 * (row * 2 + 1);
        unsigned char *y0 = y + width * row * 2;
        unsigned char *y1 = y + width * (row * 2 + 1);
        unsigned char *u0 = u + hw * row;
        unsigned char *v0 = v + hw * row;
        for (int col = 0; col < hw; col++) {
            *y0++ = s0[0];
            *y0++ = s0[3];
            *y1++ = s1[0];
            *y1++ = s1[3];
            *u0++ = avgYUV(s0[1], s0[4], s1[1], s1[4]);
            *v0++ = avgYUV(s0[2], s0[5], s1[2], s1[5]);
            s0 += 6;
            s1 += 6;
        }
    }
}

void YUVToNV12(unsigned char *src, unsigned char *dst, int width, int height) {
    int hw = width / 2;
    int hh = height / 2;
    unsigned char *y = dst;
    unsigned char *uv = dst + width * height;
    for (int row = 0; row < hh; row++) {
        unsigned char *s0 = src + width * 3 * row * 2;
        unsigned char *s1 = src + width * 3 * (row * 2 + 1);
        unsigned char *y0 = y + width * row * 2;
        unsigned char *y1 = y + width * (row * 2 + 1);
        unsigned char *uv0 = uv + width * row;
        for (int col = 0; col < hw; col++) {
            *y0++ = s0[0];
            *y0++ = s0[3];
            *y1++ = s1[0];
            *y1++ = s1[3];
            *uv0++ = avgYUV(s0[1], s0[4], s1[1], s1[4]);
            *uv0++ = avgYUV(s0[2], s0[5], s1[2], s1[5]);
            s0 += 6;
            s1 += 6;
        }
    }
}

int mapCVCode(int code) {
    switch (code) {
    case CVT_I420ToBGR:
        return cv::COLOR_YUV2RGB_I420;
    case CVT_NV12ToBGR:
        return cv::COLOR_YUV2BGR_NV12;
    case CVT_GrayToBGR:
        return cv::COLOR_GRAY2BGR;
    case CVT_YUVToBGR:
        return cv::COLOR_YUV2BGR;
    case CVT_YUVToGray:
        return -1;
    case CVT_BGRToI420:
        return cv::COLOR_RGB2YUV_I420;
    case CVT_BGRToGray:
        return cv::COLOR_BGR2GRAY;
    case CVT_BGRToYUV:
        return cv::COLOR_BGR2YUV;
    default:
        return -1;
    }
}
void I420ToNV12(int width, int height, const void *src, void *dst) {
    int planeSizeY = width * height;
    int planeSizeV = planeSizeY / 4;
    int newPlaneSizeUV = planeSizeY / 2;
    int i = 0;
    unsigned char *srcPtr = (unsigned char *)src;
    unsigned char *srcPtrV = (unsigned char *)src + planeSizeY;
    unsigned char *srcPtrU = (unsigned char *)srcPtrV + planeSizeV;
    unsigned char *dstPtr = (unsigned char *)dst;

    // copy the entire Y plane
    memcpy(dstPtr, srcPtr, planeSizeY);
    dstPtr += planeSizeY;

    // deinterlace the UV data
    for (i = 0; i < planeSizeV; i++) {
        // *dstPtr++ = srcPtrU[i];
        // *dstPtr++ = srcPtrV[i];
        *dstPtr++ = srcPtrV[i];
        *dstPtr++ = srcPtrU[i];
    }
}

void convertColorCV(const void *src, void *dst, int width, int height, int stride,
                    int code) {
    int op = mapCVCode(code);
    switch (code) {
    case CVT_I420ToBGR:
    case CVT_NV12ToBGR: {
        cv::Mat smat(height + height / 2, width, CV_8UC1, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::cvtColor(smat, dmat, op);
        break;
    }
    case CVT_GrayToBGR: {
        cv::Mat smat(height, width, CV_8UC1, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::cvtColor(smat, dmat, op);
        break;
    }
    case CVT_YUVToBGR: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::cvtColor(smat, dmat, op);
        break;
    }
    case CVT_YUVToGray: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src);
        cv::Mat dmat(height, width, CV_8UC1, (char *)dst);
        cv::extractChannel(smat, dmat, 0);
        break;
    }
    case CVT_YUVToI420: {
        YUVToI420((unsigned char *)src, (unsigned char *)dst, width, height);
        break;
    }
    case CVT_YUVToNV12: {
        YUVToNV12((unsigned char *)src, (unsigned char *)dst, width, height);
        break;
    }
    case CVT_BGRToI420: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src, stride);
        cv::Mat dmat(height + height / 2, width, CV_8UC1, (char *)dst);
        cv::cvtColor(smat, dmat, op);
        break;
    }
    case CVT_BGRToGray: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src, stride);
        cv::Mat dmat(height, width, CV_8UC1, (char *)dst);
        cv::cvtColor(smat, dmat, op);
        break;
    }
    case CVT_BGRToYUV: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::cvtColor(smat, dmat, op);
        break;
    }
    case CVT_YUVToNV12_I420: {
        I420ToNV12(width, height, src, dst);
        break;
    }
    default:
        assert(false);
        break;
    }
}

void convertColorOCL(const void *src, void *dst, int width, int height, int stride,
                     int code) {
    int op = mapCVCode(code);
    switch (code) {
    case CVT_I420ToBGR:
    case CVT_NV12ToBGR: {
        cv::Mat smat(height + height / 2, width, CV_8UC1, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::UMat tmp;
        cv::cvtColor(smat.getUMat(cv::ACCESS_READ), tmp, op);
        tmp.copyTo(dmat);
        break;
    }
    case CVT_YUVToBGR: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::UMat tmp;
        cv::cvtColor(smat.getUMat(cv::ACCESS_READ), tmp, op);
        tmp.copyTo(dmat);
        break;
    }
    case CVT_YUVToGray: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src);
        cv::Mat dmat(height, width, CV_8UC1, (char *)dst);
        cv::extractChannel(smat, dmat, 0);
        break;
    }
    case CVT_BGRToI420: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src, stride);
        cv::Mat dmat(height + height / 2, width, CV_8UC1, (char *)dst);
        cv::UMat tmp;
        cv::cvtColor(smat.getUMat(cv::ACCESS_READ), tmp, op);
        tmp.copyTo(dmat);
        break;
    }
    case CVT_BGRToGray: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src, stride);
        cv::Mat dmat(height, width, CV_8UC1, (char *)dst);
        cv::UMat tmp;
        cv::cvtColor(smat.getUMat(cv::ACCESS_READ), tmp, op);
        tmp.copyTo(dmat);
        break;
    }
    case CVT_BGRToYUV: {
        cv::Mat smat(height, width, CV_8UC3, (char *)src);
        cv::Mat dmat(height, width, CV_8UC3, (char *)dst);
        cv::UMat tmp;
        cv::cvtColor(smat.getUMat(cv::ACCESS_READ), tmp, op);
        tmp.copyTo(dmat);
        break;
    }
    case CVT_GrayToBGR:
    case CVT_YUVToI420:
    case CVT_YUVToNV12: { // ignore accel
        convertColorCV(src, dst, width, height, stride, code);
        break;
    }
    default:
        assert(false);
        break;
    }
}

void convertColor(const void *src, void *dst, int width, int height, int stride,
                  int code, bool accel) {
    convertColorCV(src, dst, width, height, stride, code);
    // if (accel) {
    //     convertColorOCL(src, dst, width, height, stride, code);
    // } else {
    //     convertColorCV(src, dst, width, height, stride, code);
    // }
}

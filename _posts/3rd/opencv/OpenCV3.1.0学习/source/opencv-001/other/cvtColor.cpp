
#include<opencv2\opencv.hpp>
#include<highgui.h>
using namespace cv;

int test1()
{
	// read image
	Mat image = imread("test.jpg");
	if (image.data == NULL)
	{
		printf("open fail.");
		return -1;
	}

	Mat dst;
	cv::cvtColor(image, dst, cv::COLOR_BGR2GRAY);

	// display image
	imshow("My Test", image);
	imshow("My Invert Image", dst);
	// ¹Ø±Õ
	waitKey(0);
	return 0;
}

// MEG_COLOR_GRAY = 0, // YYYY....
// MEG_COLOR_BGR = 1, // BGR....;  opencv;
// MEG_COLOR_RGBA = 2, // RGBA....; android ARGB_8888.
// MEG_COLOR_I420 = 3, // YYYY....U..V..; pc software;
// MEG_COLOR_YV12 = 4, // YYYY....V..U..; android software decoding.
// MEG_COLOR_NV12 = 5, // YYYY....UV..;   pc hardware, cuda, qsv
// MEG_COLOR_NV21 = 6, // YYYY....VU..;   android hardware decoding,

int WIDTH = 4;
int HEIGHT = 4;
unsigned char YUV[48] = {
	1,2,3,  1,2,3,  1,2,3,  1,2,3,
	1,2,3,  1,2,3,  1,2,3,  1,2,3,
	1,2,3,  1,2,3,  1,2,3,  1,2,3,
	1,2,3,  1,2,3,  1,2,3,  1,2,3
};

unsigned char YUV_2_BGR[48] = {
	0, 123, 0, 0, 123, 0, 0, 123, 0, 0, 123, 0,
	0, 123, 0, 0, 123, 0, 0, 123, 0, 0, 123, 0,
	0, 123, 0, 0, 123, 0, 0, 123, 0, 0, 123, 0,
	0, 123, 0, 0, 123, 0, 0, 123, 0, 0, 123, 0 };

unsigned char I420[24] = {
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3, 3, 3 };

unsigned char YV12[24] = {
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	3, 3, 3, 3,
	2, 2, 2, 2 };

unsigned char NV12[24] = {
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	2, 3, 2, 3,
	2, 3, 2, 3 };

unsigned char NV21[24] = {
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	3, 2, 3, 2,
	3, 2, 3, 2 };

unsigned char RGBA[64] = {
	0, 151, 0, 5, 0, 151, 0, 6, 0, 151, 0, 7, 0, 151, 0, 8,
	0, 151, 0, 5, 0, 151, 0, 6, 0, 151, 0, 7, 0, 151, 0, 8,
	0, 151, 0, 5, 0, 151, 0, 6, 0, 151, 0, 7, 0, 151, 0, 8,
	0, 151, 0, 5, 0, 151, 0, 6, 0, 151, 0, 7, 0, 151, 0, 8 };

unsigned char YUV420_2_BGR[48] = {
	0, 151, 0, 0, 151, 0, 0, 151, 0, 0, 151, 0,
	0, 151, 0, 0, 151, 0, 0, 151, 0, 0, 151, 0,
	0, 151, 0, 0, 151, 0, 0, 151, 0, 0, 151, 0,
	0, 151, 0, 0, 151, 0, 0, 151, 0, 0, 151, 0 };

unsigned char YUV420_2_GRAY[16] = {
	89, 89, 89, 89,
	89, 89, 89, 89,
	89, 89, 89, 89,
	89, 89, 89, 89 };

unsigned char YUV420_2_BGR_CLIP[48] = {
	0, 151, 0, 0, 151, 0,
	0, 151, 0, 0, 151, 0 };

unsigned char YUV420_2_BGR_2_GRAY[16] = {
	89, 89, 89, 89,
	89, 89, 89, 89,
	89, 89, 89, 89,
	89, 89, 89, 89 };

unsigned char GRAY[16] = {
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1 };
unsigned char GRAY_CLIP[4] = {
	1, 1,
	1, 1 };

unsigned char GRAY_2_BGR[48] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void printT(unsigned char* p,int size)
{
	char szText[10240];
	int j = 0; 
	for (int i = 0; i < size; i++) {
		szText[j++] = ',';
		szText[j++] = p[i];
	}
	printf(szText);
}

void ASSERT(bool c) {
	if (!c)
	{
		printf("game over");
		exit(-1);
	}
}

int testColor() {
	Mat s_bgr(4, 4, CV_8UC3, YUV420_2_BGR);
	Mat s_rgba(4, 4, CV_8UC4, RGBA);
	Mat s_yuv(4, 4, CV_8UC3, YUV);
	Mat s_i420(6, 4, CV_8UC1, I420);
	Mat s_YV12(6, 4, CV_8UC1, YV12);
	Mat s_NV12(6, 4, CV_8UC1, NV12);
	Mat s_NV21(6, 4, CV_8UC1, NV21);
	Mat s_gray(4, 4, CV_8UC1, GRAY);

	Mat dst[100];

	cvtColor(s_bgr, dst[0], CV_BGR2GRAY);
	ASSERT(memcmp(dst[0].data, YUV420_2_BGR_2_GRAY, WIDTH * HEIGHT) == 0);

	cvtColor(s_rgba, dst[1], CV_RGBA2GRAY);
	ASSERT(memcmp(dst[1].data, YUV420_2_BGR_2_GRAY, WIDTH * HEIGHT) == 0);

	cv::resize(s_bgr, dst[2], cv::Size(), 0.5, 0.5);
	ASSERT(memcmp(dst[2].data, YUV420_2_BGR_CLIP, WIDTH/2 * HEIGHT/2 * 3) == 0);

	cvtColor(s_yuv, dst[3], CV_YUV2BGR);
	ASSERT(memcmp(dst[3].data, YUV_2_BGR, WIDTH * HEIGHT * 3) == 0);

	cvtColor(s_i420, dst[4], CV_YUV2BGR_I420);
	ASSERT(memcmp(dst[4].data, YUV420_2_BGR, 48) == 0);

	cvtColor(s_YV12, dst[5], CV_YUV2BGR_YV12);
	ASSERT(memcmp(dst[5].data, YUV420_2_BGR, 48) == 0);

	cvtColor(s_NV12, dst[6], CV_YUV2BGR_NV12);
	ASSERT(memcmp(dst[6].data, YUV420_2_BGR, 48) == 0);

	cvtColor(s_NV21, dst[7], CV_YUV2BGR_NV21);
	ASSERT(memcmp(dst[7].data, YUV420_2_BGR, 48) == 0);

	cvtColor(s_gray, dst[8], CV_GRAY2BGR);
	ASSERT(memcmp(dst[8].data, GRAY_2_BGR, WIDTH * HEIGHT*3) == 0);

	cv::resize(s_gray, dst[9], cv::Size(), 0.5, 0.5);
	ASSERT(memcmp(dst[9].data, GRAY_CLIP, WIDTH/2*HEIGHT/2) == 0);

	cvtColor(s_i420, dst[10], CV_YUV2GRAY_I420);
	ASSERT(memcmp(dst[10].data, GRAY, WIDTH * HEIGHT) == 0);

	return 0;
}

int testBGR2BGRA() {
	// read image
	Mat image = imread("C:\\work\\megcore\\data\\frame25.jpg");
	if (image.data == NULL)
	{
		printf("open fail.");
		return -1;
	}

	Mat dst;
	cv::cvtColor(image, dst, cv::COLOR_BGR2RGBA);

	// display image
	imshow("src", image);
	imshow("dst1", dst);
	Mat dst2;
	cv::cvtColor(dst, dst2, cv::COLOR_RGBA2BGR);
	imshow("dst2", dst2);

	// ¹Ø±Õ
	waitKey(0);
	return 0;
}

int mytest(int argc, char** argv)
{
	testColor();
	//testBGR2BGRA();
	return 0;
}



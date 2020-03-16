
#include<opencv2\opencv.hpp>
#include<highgui.h>

#include<assert.h>

using namespace cv;

void printMat(Mat& mat) {
	static int num = 1;
	printf("%03d:%x --- %d,%d,%d\n", num++,mat.data, mat.cols, mat.rows, mat.type());
}

//如果re
void resizeAssert(int w, int h, int type, void* data, bool ret) {
	void* pSrc = malloc(200*200*3);
	memset(pSrc, 5, 200 * 200 * 3);
	Mat image(200, 200, CV_8UC3, pSrc);
	if (data == nullptr) {
		Mat dst(w, h, type);
		printMat(dst);
		void*p = dst.data;
		cv::resize(image, dst, cv::Size(100, 100), 0, 0);
		printMat(dst);
		assert(ret == (p == dst.data));
	}
	else {
		Mat dst(w, h, type,data);
		printMat(dst);
		cv::resize(image, dst, cv::Size(100, 100), 0, 0);
		printMat(dst);
		assert(ret == (data == dst.data));
	}
	
}

/*
结论：resize内存分配结论
resize( InputArray src, OutputArray dst,
Size dsize, double fx = 0, double fy = 0,
int interpolation = INTER_LINEAR );
1,如果dst内存是用户指定的,则dst的cols，rows, type必须与预期的一致，否则resize重新分配内存。
2,如果dst内存是Mat内部分配的，则只要dst的data大小比预期的大，就不重新分配内存。
*/
int ResizeMemory(int argc, char** argv) {
	void* pDst = malloc(200 * 200 * 3);
	resizeAssert(100, 100, CV_8UC3, pDst, true);

	//same type, same w*h
	resizeAssert(50, 200, CV_8UC3, pDst, false);
	resizeAssert(200, 50, CV_8UC3, pDst, false);

	//same type, w*h < expect w*h
	resizeAssert(50, 100, CV_8UC3, pDst, false);
	resizeAssert(100, 50, CV_8UC3, pDst, false);//5

												//same type, w*h > expect w*h
	resizeAssert(100, 150, CV_8UC3, pDst, false);
	resizeAssert(150, 100, CV_8UC3, pDst, false);

	//not same type, w*h == expect w*h
	resizeAssert(100, 100, CV_8UC1, pDst, false);
	resizeAssert(100, 100, CV_8UC4, pDst, false);//9

												 ///
	free(pDst);
	pDst = nullptr;//
	resizeAssert(100, 100, CV_8UC3, pDst, true);//10

	resizeAssert(50, 200, CV_8UC3, pDst, true);//注意！！！
	resizeAssert(200, 50, CV_8UC3, pDst, true);//注意！！！

	resizeAssert(50, 100, CV_8UC3, pDst, false);
	resizeAssert(100, 50, CV_8UC3, pDst, false);
	resizeAssert(100, 150, CV_8UC3, pDst, true);//15 //注意!!!
	resizeAssert(150, 100, CV_8UC3, pDst, true);//注意!!!

	resizeAssert(100, 100, CV_8UC1, pDst, false);
	resizeAssert(100, 100, CV_8UC4, pDst, true);//18  //注意!!!
												// 关闭
	return 0;
}

int ResizeSame(int argc, char** argv) {
	// read image
	Mat image = imread("test.jpg");
	if (image.data == NULL)
	{
		printf("open fail.");
		return -1;
	}
	Mat dst;
	cv::resize(image, dst, cv::Size(100, 100), 0, 0);

}

int TestResize(int argc, char** argv)
{
	return ResizeMemory(argc, argv);
}
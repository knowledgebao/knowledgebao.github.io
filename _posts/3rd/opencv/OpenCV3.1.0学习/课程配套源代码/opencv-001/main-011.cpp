#include <opencv2/opencv.hpp> 
#include <iostream> 
using namespace cv;

int chapter011(int argc, char** argv) {
	Mat src, dst;
	src = imread("test.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	Mat mBlur;
	medianBlur(src, mBlur, 3);
	imshow("medianBlur", mBlur);

	bilateralFilter(src, dst, 10, 100, 5);
	imshow("bilateralFilter", dst);

	Mat resultImg;
	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst, resultImg, -1, kernel, Point(-1, -1), 0);
	imshow("filter2D", resultImg);

	waitKey(0);
	return 0;

}
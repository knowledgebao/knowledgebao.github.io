#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

namespace chapter016 {
	using namespace cv;
	Mat src, gray_src, dst;
	int threshold_value = 127;
	int threshold_max = 255;
	int type_value = 2;
	int type_max = 4;
	const char* output_title = "binary image";
	void Threshold_Demo(int, void*);
	int chapter016(int argc, char** argv) {
		src = imread("test.jpg");
		if (!src.data) {
			printf("could not load image...\n");
			return -1;
		}
		imshow("input image", src);
		
		namedWindow(output_title, WINDOW_AUTOSIZE);
		createTrackbar("Threshold Value:", output_title, &threshold_value, threshold_max, Threshold_Demo);
		createTrackbar("Type Value:", output_title, &type_value, type_max, Threshold_Demo);
		Threshold_Demo(0, 0);

		waitKey(0);
		return 0;
	}

	void Threshold_Demo(int, void*) {
		cvtColor(src, gray_src, CV_BGR2GRAY);
		threshold(src, dst, threshold_value, threshold_max, THRESH_TRIANGLE & type_value);
		imshow(output_title, dst);
	}

}

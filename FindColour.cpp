#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

int main() {

	cv::Mat lastPic, imgHSV, mask;
	int hmin = 4, smin = 0, vmin = 130;
	int hmax = 29, smax = 255, vmax = 255;

	string path = "cicek.jpg";
	cv::Mat img = cv::imread(path);
	cv::resize(img, lastPic,cv::Size(), 0.7, 0.7);

	cv::cvtColor(lastPic, imgHSV, cv::COLOR_BGR2HSV);

	//With the help of trackbar we can find our desired colour and save it's values
	//Here is yellow
	/*
	cv::namedWindow("Track Bar", (640, 200));
	cv::createTrackbar("Hue Min", "Track Bar", &hmin, 179);
	cv::createTrackbar("Hue Max", "Track Bar", &hmax, 179);
	cv::createTrackbar("Sat Min", "Track Bar", &smin, 255);
	cv::createTrackbar("Sat Max", "Track Bar", &smax, 255);
	cv::createTrackbar("Val Min", "Track Bar", &vmin, 255);
	cv::createTrackbar("Val Max", "Track Bar", &vmax, 255);*/

	while (true) {
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(imgHSV, lower, upper, mask);

		cv::imshow("Original", lastPic);
		cv::imshow("HSV", imgHSV);
		cv::imshow("Mask", mask);
		cv::waitKey(1);
	}

	return 0;
}
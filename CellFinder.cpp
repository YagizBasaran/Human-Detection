#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

cv::Mat colorFinder(string path) {
	//Find the colour with trackbar and type here
	//Everything black except desired colour, it should be white
	cv::Mat imgHSV, mask;
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 47, smax = 243, vmax = 255;

	cv::Mat img = cv::imread(path);

	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	//With the help of trackbar we can find our desired colour and save it's values
	//cv::namedWindow("Track Bar", (640, 200));
	//cv::createTrackbar("Hue Min", "Track Bar", &hmin, 179);
	//cv::createTrackbar("Hue Max", "Track Bar", &hmax, 179);
	//cv::createTrackbar("Sat Min", "Track Bar", &smin, 255);
	//cv::createTrackbar("Sat Max", "Track Bar", &smax, 255);
	//cv::createTrackbar("Val Min", "Track Bar", &vmin, 255);
	//cv::createTrackbar("Val Max", "Track Bar", &vmax, 255);

	//while (true) {
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(imgHSV, lower, upper, mask);

		//cv::imshow("Original", img);
		//cv::imshow("Mask", mask);
		//cv::waitKey(1);
	//}

	return mask;
}

int main() {

	string path = "Cells01.jpg"; // PATH

	cv::Mat img = cv::imread(path);
	cv::Mat cellImg = colorFinder(path); //black and white
	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy; // do not care

	cv::findContours(cellImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cout << contours.size() << endl;

	vector<vector<cv::Point>> conPoly(contours.size());
	vector<cv::Rect> rectangles(contours.size());

	for (int i = 0; i < contours.size(); i++) {

		cout << cv::contourArea(contours[i]) << endl;
		if (cv::contourArea(contours[i]) > 48) {
			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // can delete peri and put a fixed num

			//cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 2); //for adjoining lines

			rectangles[i] = cv::boundingRect(conPoly[i]);
			cv::Point center = cv::Point((rectangles[i].tl().x + rectangles[i].br().x) / 2, (rectangles[i].tl().y + rectangles[i].br().y) / 2);
			//cv::rectangle(img, rectangles[i].tl(), rectangles[i].br(), cv::Scalar(0, 255, 0), 2); // rectangle
			cv::circle(img, center, 30, cv::Scalar(0, 0, 255), 2); // circle
		}
	}

	cv::imshow("Last Pic", cellImg);
	cv::imshow("Normal Pic", img);
	cv::waitKey(0);
	return 0;
}

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

void getContours(cv::Mat imgDil, cv::Mat img) {

	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy; // 4 integer values


	cv::findContours(imgDil,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);//RETR_EXTERNAL, CHAIN_APPROX_SIMPLE
	//cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

	vector<vector<cv::Point>> conPoly(contours.size());
	vector<cv::Rect> rectangles(contours.size());
	string shapes;

	for (int i = 0; i < contours.size(); i++) {
		cout << cv::contourArea(contours[i]) << endl;

		if (cv::contourArea(contours[i]) > 1000) {
			
			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // can delete peri and put a fixed num

			cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 2);

			cout << conPoly[i].size() << endl;

			rectangles[i] = cv::boundingRect(conPoly[i]);
			cv::rectangle(img, rectangles[i].tl(), rectangles[i].br(), cv::Scalar(0, 255, 0), 3);

			int cornerNum = (int)conPoly[i].size();

			if (cornerNum == 3) shapes = "triangle";
			else if (cornerNum == 4) shapes = "rectangle";
			else shapes = "circlar";

			cv::putText(img, shapes, { rectangles[i].x, rectangles[i].y +20 }, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(255, 255, 255), 3);
		}
	}

}

int main() {

	cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	string path = "shapes1.png";
	cv::Mat img = cv::imread(path);

	cv::resize(img, img, cv::Size(600,300));

	cv::cvtColor(img, imgGray, cv::COLOR_RGB2GRAY); 
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 5, 0); 
	cv::Canny(imgBlur, imgCanny, 40, 80);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	cv::imshow("Image", img);
	//cv::imshow("Imagegray", imgGray);
	//cv::imshow("Imageblur", imgBlur);
	//cv::imshow("Imagecanny", imgCanny);
	//cv::imshow("ImageDil", imgDil);

	cv::waitKey(0);

	return 0;
}
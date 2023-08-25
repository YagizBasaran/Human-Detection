#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

int main()
{
	//Image drawing
					//8 bit, unsigned, 3colors
	cv::Mat img(500, 500, CV_8UC3, cv::Scalar(150, 100, 180));// B-R-G = Blue Red Green, it is reversed at opencv not like RGB

	cv::circle(img, cv::Point(250, 250), 120, cv::Scalar(100, 175, 200), cv::FILLED); //Filled or thickness int (7, 10, etc) 
	cv::rectangle(img, cv::Point(10,80),cv::Point(400,40), cv::Scalar(0, 0, 0), 5);
					//left top vertex     //right bottom vertex
	cv::line(img, cv::Point(20, 470), cv::Point(470, 470), cv::Scalar(210, 10, 24),4);
	cv::putText(img, "Yagiz Basaran Lambo", cv::Point(20, 250), cv::FONT_ITALIC, 1, cv::Scalar(0, 210, 0), 2);

	cv::imshow("My Picture", img);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
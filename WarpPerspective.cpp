#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

int main()
{
	float w = 350; float h = 550;
	cv::Mat matrix, imgWarp;

	string path = "Kartlarfoto.jpg";
	cv::Mat img = cv::imread(path);
	//Card 1
	//                  top left- top right- bottom left- bottom right
	cv::Point2f src[4] = { {31,233},{113,231},{5,335},{112,325} };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = cv::getPerspectiveTransform(src, dst);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

	cv::imshow("Card1", imgWarp);

	//Card 2
	cv::Point2f src2[4] = { {266,198},{248,164},{150,203},{147,169} };
	cv::Point2f dst2[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = cv::getPerspectiveTransform(src2, dst2);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

	cv::imshow("Card2", imgWarp);

	cv::imshow("Original Image", img);


	cv::waitKey(0);

	return 0;
}
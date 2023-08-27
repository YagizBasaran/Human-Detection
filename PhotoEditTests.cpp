#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

int main()
{
    string path = "psycocb.jpg"; // Your photo path
    cv::Mat img = cv::imread(path);

    cv::Mat imgDiffColor, imgBlur, imgCanny, imgDilate, imgErode;

    cv::cvtColor(img, imgDiffColor, cv::COLOR_RGB2GRAY); //_RGB2HLS = try this :) //_RGB2XYZ = pink pale
    cv::GaussianBlur(imgDiffColor, imgBlur, cv::Size(3,3), 5, 0); // Size needs odd numbers.
    cv::Canny(imgBlur, imgCanny, 40, 80); //Common practice to canny with blur image it gives less lines // lower the values more the lines
    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::dilate(imgCanny, imgDilate, kernel); // Dilating
    cv::erode(imgDilate, imgErode, kernel); // Erozyon

    cv::imshow("Christian Bale", img);
    cv::imshow("Gray CB", imgDiffColor);
    cv::imshow("Blurred CB", imgBlur);
    cv::imshow("Canny CB", imgCanny);
    cv::imshow("Dilate CB", imgDilate);
    cv::imshow("Erode CB", imgErode);

    cv::Mat imgCrop, imgResize;
    cv::resize(img, imgResize, cv::Size(), 0.5, 0.5); // use Size() for specific size because it doesnt protects uniform // double x and y protects the picture
    //cv::resize(img, imgResize, cv::Size(250,750)); // 250 x 750
    cv::Rect roi(0, 0, 300, 300);
    imgCrop = img(roi);

    cv::imshow("Resized CB", imgResize);
    cv::imshow("Crop CB", imgCrop);

    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}

// Test1.cpp : This file contains the 'main' function. Program execution begins and ends there

#include <cstdio>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

void pictureReadnOpen(string filePath) {

    cv::Mat pic;
    pic = cv::imread(filePath);

    if (pic.data) {
        cv::namedWindow("Batman");
        cv::imshow("Batman", pic);
        cv::waitKey();
        cv::destroyAllWindows();
    }
    else {
        cout << "Cannot read the picture. File Path: " << filePath << endl;
    }

}

void videoReadnOpen(string filePath) { // Videos are actually series of images.

    cv::VideoCapture vid(filePath);
    //vid.open(filePath);

    cv::Mat img;
    int fps = 23;

    if (vid.isOpened()) {
        cout << "Opening" << endl;
        while (vid.read(img)) {
            cv::imshow("Test Video", img);
            if (cv::waitKey(fps) == 27) {//when "esc" is pressed, video ends
                break;
                cv::destroyAllWindows();
            }
        }
    }
    else {
        cout << "Cannot open the video. File Path: " << filePath << endl;
    }

    //cv::waitKey(20); cv::waitKey(10); //can choose fps(speed) here

}

void webcamReadnOpen(int ch) { // cam channel "0" for pc cams
                               // ip cam is same just change it to "string ip"
    cv::VideoCapture cam;

    if (cam.open(ch)) {
        cout << "Cam is open rn." << endl;
        cv::Mat img;
        while (cam.grab()) {
            cam.retrieve(img);
            cv::imshow("Webcam Rty", img);
            if (cv::waitKey(20) == 27) {//when "esc" is pressed, video ends
                break;
                cv::destroyAllWindows();
            }
        }
    }
    else {
        cout << "Cam is not open might be wrong channel." << endl;
    }

    //SHORTEST VERSION
    //cv::VideoCapture cam(0);
    //cv::Mat img;

    //while (true) {
    //    cam.read(img);
    //    imshow("Webcam", img);
    //    cv::waitKey(1);
    //}
}

int main()
{

    pictureReadnOpen("unnamed.jpg");

    videoReadnOpen("yagizTestVid.mp4");

    webcamReadnOpen(0);

    return 0;
}



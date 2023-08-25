#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>

using namespace std;

void findFaceFromPic(string path) {

	cv::Mat photo = cv::imread(path);

	cv::CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml"); // Your cascade location

	if (faceCascade.empty()) cout << "XML file is not loaded." << endl;
	else {
		vector<cv::Rect> faces;
		faceCascade.detectMultiScale(photo, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++) {
			cv::rectangle(photo, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);

		}

	}

	cv::imshow("Müdür", photo);
	cv::waitKey(0);
	cv::destroyWindow("Müdür");


}

void findFaceFromCam(int ch) {
	cv::VideoCapture cam;

	cv::CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml");

	if (cam.open(ch)) {
		cout << "Cam is open rn." << endl;
		cv::Mat img;

		if (faceCascade.empty()) cout << "XML file is not loaded." << endl;
		else {

			while (cam.grab()) {
				vector<cv::Rect> faces;

				cam.retrieve(img);
				faceCascade.detectMultiScale(img, faces, 1.1, 10);

				for (int i = 0; i < faces.size(); i++) {
					cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
					cv::putText(img, "Human", { faces[i].x, faces[i].y - 20 }, cv::FONT_HERSHEY_TRIPLEX, 1, cv::Scalar(240, 214, 45), 2);
				}
				cv::imshow("Webcam Rty", img);

				if (cv::waitKey(5) == 27) {//when "esc" is pressed, video ends
					break;
					cv::destroyAllWindows();
				}
			}

		}
	}
	else {
		cout << "Cam is not open might be wrong channel." << endl;
	}
}

int main() {

	cout << "Press 1 for finding pictures from a picture, 2 for webcam." << endl;
	int sel; cin >> sel;

	if (sel == 1) {

		cout << "Type the path: " << endl;
		string path; cin >> path;

		findFaceFromPic(path); 

	}
	else if (sel == 2) {
		cout << "Type the channel (mostly 0 or 1): " << endl;
		int path; cin >> path;

		findFaceFromCam(path);
	}


	return 0;
}
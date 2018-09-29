#include <iostream>
#include <opencv2/opencv.hpp>

int sec = 0;

void trackbar(int, void *param) {
	cv::VideoCapture cap = *((cv::VideoCapture*)param);
	cap.set(CV_CAP_PROP_POS_MSEC, sec * 1000);
}

void play_vid(std::string const &path) {
	cv::VideoCapture cap(path);

	if(!cap.isOpened()) {
		printf("No such specified file.\n");
		return;
	}

	cv::Mat frame;

	double total_time = cap.get(CV_CAP_PROP_FRAME_COUNT) / cap.get(CV_CAP_PROP_FPS);
	cv::namedWindow("Frame", 1);
	cv::createTrackbar("Position", "Frame", &sec, (int)total_time, trackbar, &cap);

	while(true) {
		cap >> frame;

		if (!frame.empty()) {
			cv::imshow("Frame", frame);
			cv::waitKey(1);
		}
		else {
			cv::destroyWindow("Frame");
			cap.release();
			break;
		}
	}
}

int main(int argc, char *argv[]) {

	if(argc == 2)
		play_vid(argv[1]);
	else
		printf("Input path as argument\n");

	return 0;
}
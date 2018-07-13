#include "mtcnn.h"
#include <opencv2/opencv.hpp>
#include <sys/time.h>

using namespace cv;

#define MAXFACEOPEN 0 //设置是否开关最大人脸调试，1为开，其它为关

double get_current_time()
{
    struct timeval tv;
	
    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}




void test_video() {
	char *model_path = "../models";
	MTCNN mtcnn(model_path);
	mtcnn.SetMinFace(40);
	cv::VideoCapture mVideoCapture(0);
	if (!mVideoCapture.isOpened()) {
		return;
	}
	cv::Mat frame;
	mVideoCapture >> frame;
	while (!frame.empty()) {
		mVideoCapture >> frame;
		if (frame.empty()) {
			break;
		}

		clock_t start_time = clock();
		
		ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(frame.data, ncnn::Mat::PIXEL_BGR2RGB, frame.cols, frame.rows);
		std::vector<Bbox> finalBbox;
#if(MAXFACEOPEN==1)
		mtcnn.detectMaxFace(ncnn_img, finalBbox);
#else
		mtcnn.detect(ncnn_img, finalBbox);
#endif
		const int num_box = finalBbox.size();
		std::vector<cv::Rect> bbox;
		bbox.resize(num_box);
		for(int i = 0; i < num_box; i++){
			bbox[i] = cv::Rect(finalBbox[i].x1, finalBbox[i].y1, finalBbox[i].x2 - finalBbox[i].x1 + 1, finalBbox[i].y2 - finalBbox[i].y1 + 1);
		
			for (int j = 0; j<5; j = j + 1)
			{
				//cv::circle(frame, cvPoint(finalBbox[i].ppoint[j], finalBbox[i].ppoint[j + 5]), 2, CV_RGB(0, 255, 0), CV_FILLED);
				cv::circle(frame, cvPoint(finalBbox[i].landmark.x[j], finalBbox[i].landmark.y[j]), 2, CV_RGB(0, 255, 0), CV_FILLED);
			}
		}
		for (vector<cv::Rect>::iterator it = bbox.begin(); it != bbox.end(); it++) {
			rectangle(frame, (*it), Scalar(0, 0, 255), 2, 8, 0);
		}
		imshow("face_detection", frame);
		clock_t finish_time = clock();
		double total_time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
		std::cout << "time" << total_time * 1000 << "ms" << std::endl;
	
		int q = cv::waitKey(10);
		if (q == 27) {
			break;
		}
	}
	return ;
}

int test_picture(){
	char *model_path = "../models";
	MTCNN mtcnn(model_path);

	clock_t start_time = clock();
	
	
	
	cv::Mat image;
	image = cv::imread("../sample.jpg");
	ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(image.data, ncnn::Mat::PIXEL_BGR2RGB, image.cols, image.rows);
	std::vector<Bbox> finalBbox;
	
	double begin = get_current_time();
	
#if(MAXFACEOPEN==1)
	mtcnn.detectMaxFace(ncnn_img, finalBbox);
#else
	mtcnn.detect(ncnn_img, finalBbox);
#endif
	double end = get_current_time();
	
	std::cout<<"detect cost:"<< end - begin<< std::endl;

	const int num_box = finalBbox.size();
	std::vector<cv::Rect> bbox;
	bbox.resize(num_box);
	for (int i = 0; i < num_box; i++) {
		bbox[i] = cv::Rect(finalBbox[i].x1, finalBbox[i].y1, finalBbox[i].x2 - finalBbox[i].x1 + 1, finalBbox[i].y2 - finalBbox[i].y1 + 1);

		for (int j = 0; j<5; j = j + 1)
		{
			//cv::circle(image, cvPoint(finalBbox[i].ppoint[j], finalBbox[i].ppoint[j + 5]), 2, CV_RGB(0, 255, 0), CV_FILLED);
			cv::circle(image, cvPoint(finalBbox[i].landmark.x[j], finalBbox[i].landmark.y[j]), 2, CV_RGB(0, 255, 0), CV_FILLED);
		}
	}
	
	for (vector<cv::Rect>::iterator it = bbox.begin(); it != bbox.end(); it++) {
		rectangle(image, (*it), Scalar(0, 0, 255), 2, 8, 0);
	}

	//imshow("face_detection", image);
	cv::imwrite("result.jpg", image);
	
	clock_t finish_time = clock();
	double total_time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
	std::cout << "time" << total_time * 1000 << "ms" << std::endl;

	cv::waitKey(0);

}

int main(int argc, char** argv) {
	
	//test_video();
	test_picture();
	return 0;
}
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
 Will display corners using the Corner Harris on live videoStream Frames
 */
int main(int argc, char* argv[]) {
    
    int blockSize = 2;
    int kSize = 3;
    double k = 0.04;

    
    VideoCapture *capdev;
    capdev = new VideoCapture(0);
    if (!capdev->isOpened()) {
        cout << "Unable to open video device\n";
        return -1;
    }

    
    namedWindow("Video", 1);

    Mat frame;

    while (true) {
        *capdev >> frame; 
        if (frame.empty()) {
            cout << "frame is empty\n";
            break;
        }
        

        char key = waitKey(10);

        // run Harris corner detector
        Mat grayscale;
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);
        Mat dst = Mat::zeros(grayscale.size(), CV_32FC1);

        //cornerHarris detecction
        cornerHarris(grayscale, dst, blockSize, kSize, k);

        double min, max;
        cv::minMaxLoc(dst, &min, &max);
        float thresh = 0.1 * max;
        for (int i = 0; i < dst.rows ; i++) {
            for(int j = 0; j < dst.cols; j++) {
                if (dst.at<float>(i,j) > thresh) {
                    circle(frame, Point(j,i), 1, Scalar(147, 20, 255), 2);
                }
            }
        }

        imshow("Video", frame);

        if (key == 'q') { 
            break;
        }
    }

    destroyAllWindows();

    return 0;
}
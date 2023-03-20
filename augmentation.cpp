/*
by:
    Aadhar Bansal
    Pranav K Nair
*/

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "functions.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){

    //Declaring the size of the chessboard Pattern (9, 6)
    cv::Size chessBoardSize(9, 6); 
    cv::Mat chessboardCameraMatrix;


    vector<Vec3f> chessBoardPoints; 
    vector<vector<Point2f>> chessboardCornerList;
    vector<vector<Vec3f>> chessboardPointList;
    

    // Calibration Frames needed
    int CALIBRATION_FRAME_NEEDED = 5;                     
    cv::Mat chessboardDistCoeffs;            
    vector<Mat> chessboardR, chessboardT; 


    VideoCapture *capdev;
    //The 0 is for the webcam, and 2 for the external webcam as two webcam are used for the project
    // capdev = new VideoCapture(0);
    capdev = new VideoCapture(2);
    if (!capdev->isOpened())
    {
        cout << "Unable to open video device\n";
        return -1;
    }

    
    namedWindow("Video", 1);


    chessBoardPoints = worldPoints(chessBoardSize);
    Mat frame;

    int count = 0;
    while (true)
    {

        *capdev >> frame; 
        if (frame.empty())
        {
            cout << "frame is empty\n";
            break;
        }

        // resize the frame to 1/2 of the original size
        resize(frame, frame, Size(), 0.5, 0.5);

        // Final frame to be displayed
        Mat finalFrame = frame.clone(); 

        char key = waitKey(10);

        // chessboard corners
        vector<Point2f> chessboardCorners; 
        
        //calling function to get the chessboard corners vector
        bool chessboardCornersFlag = chessboardCorners2Vec(frame, chessBoardSize, chessboardCorners);
        
        
        if (chessboardCornersFlag)
        { 
            //projecting the chessboaed corners
            drawChessboardCorners(finalFrame, chessBoardSize, chessboardCorners, chessboardCornersFlag);
        }

        
        if (key == 's')
        { 
            
            cout<<"Atleast " <<CALIBRATION_FRAME_NEEDED<<" times calibration to be done";
            
            //Calibrating the chessboard
            if (chessboardCornersFlag)
            {
                count += 1;
                cout << "Calibration done " << count << " times" << endl;
                chessboardCornerList.push_back(chessboardCorners);
                
                //Pushing the world points to the vector
                chessboardPointList.push_back(chessBoardPoints);
            }
            else
            {
                cout << "Calibrate again" << endl;
            }
        }

        else if (key == 'c')
        { // calibrate the camera for chessboard
            if (chessboardPointList.size() < CALIBRATION_FRAME_NEEDED)
            { // not enough calibration frames
                cout << "Do calibration again" << endl;
            }
            else
            {
                cout << "calibrate camera" << endl;
                // calibrate the camera
                Mat coeff_before_calibration = chessboardDistCoeffs.clone();
                double chessboardError = calibrateCamera(chessboardPointList, chessboardCornerList, Size(frame.rows, frame.cols), chessboardCameraMatrix, chessboardDistCoeffs, chessboardR, chessboardT);
                
                cout << "Camera Matrix: " << endl;
                Matrix(chessboardCameraMatrix);
                
                cout << "Distortion Coefficients: " << endl;
                Matrix(chessboardDistCoeffs);
                cout << "Re-projection Error: " << chessboardError << endl;
            }
        }

        

        if (chessboardDistCoeffs.rows != 0)
        {
            // extractChessboardCorners of current frame
            vector<Point2f> currCorners; // the image points found by findChessboardCorners
            bool foundCurrCorners = chessboardCorners2Vec(frame, chessBoardSize, currCorners);

            if (foundCurrCorners)
            {
                Mat rvec, tvec; // output arrays for solvePnP()
                bool status = solvePnP(chessBoardPoints, currCorners, chessboardCameraMatrix, chessboardDistCoeffs, rvec, tvec);

                if (status)
                { // solvePnP() succeed
                    // project outside corners
                    Put4Corners(finalFrame, chessBoardPoints, rvec, tvec, chessboardCameraMatrix, chessboardDistCoeffs);

                    // project a virtual object
                    // char keyn = waitKey(10);

                    
                    createnProjectVO(finalFrame, rvec, tvec, chessboardCameraMatrix, chessboardDistCoeffs);

                    
                }
            }
        }

        imshow("Video", finalFrame);
        if (key == 'q'){
            break;
        }

    }
    return 0;
}
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "functions.h" 

using namespace std;
using namespace cv;

/*
 Generate vector<Vec3f> of the size given of the x and y coordinates
 */
vector<Vec3f> worldPoints(Size coorSize) {
    vector<Vec3f> points;
    for (int i = 0; i < coorSize.height; i++) {
        for (int j = 0; j < coorSize.width; j++) {
            Vec3f point = Vec3f(j, -i, 0);
            points.push_back(point);
        }
    }
    return points;
}



/*
function detects the corners of the chessboard object
return the vector of the Point2f of corners
*/
bool chessboardCorners2Vec(Mat &frame, Size patternSize, vector<Point2f> &corners) {
    bool cornersFlag = findChessboardCorners(frame, patternSize, corners);
    //corners detected
    if (cornersFlag) {

        Mat grayscale;
        //Convert fram to the grayscale as single channel is required
        Size subPixWinSize(10, 10);
        cvtColor(frame, grayscale, COLOR_BGR2GRAY); 
        TermCriteria termCrit(TermCriteria::COUNT|TermCriteria::EPS, 1, 0.1);
        cornerSubPix(grayscale, corners, subPixWinSize, Size(-1, -1), termCrit);
    }
    return cornersFlag;
} 



void Matrix(Mat &matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        cout << "[";
        for (int j = 0; j < matrix.cols; j++) {
            cout << matrix.at<double>(i, j) << "\t";
        }
        cout << "]\n";
    }
}





    void Put4Corners(Mat &frame, vector<Vec3f> points, Mat rvec, Mat tvec, Mat cameraMatrix, Mat distCoeffs) {
        vector<Point2f> imagePoints;
        projectPoints(points, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);
        int index[] = {0, 8, 45, 53};
        for (int i : index) {
            circle(frame, imagePoints[i], 5, Scalar(255, 221, 0), 4);
        }
    }


    void createnProjectVO(Mat &frame, Mat rvec, Mat tvec, Mat cameraMatrix, Mat distCoeffs)
    {
        vector<Vec3f> objectPoints;

        
        // objectPoints = constructObjectCuboid();
             
        // objectPoints = constructObjectCircle();
        
        objectPoints = constructObjectSphere();

        // objectPoints = constructObjectAll();
        

        vector<Point2f> projectedPoints;
        projectPoints(objectPoints, rvec, tvec, cameraMatrix, distCoeffs, projectedPoints);
        
        for (int i = 0; i < projectedPoints.size(); i++)
        {
            circle(frame, projectedPoints[i], 1, Scalar(255, 221, 0), 4);
        }
        projectObjects(frame, projectedPoints);
    }


    void projectObjects(Mat &frame, vector<Point2f> p) {

            line(frame, p[0], p[1], Scalar(4, 20, 255), 2);
            line(frame, p[0], p[2], Scalar(4, 20, 255), 2);
            line(frame, p[1], p[3], Scalar(4, 20, 255), 2);
            line(frame, p[2], p[3], Scalar(4, 20, 255), 2);
            line(frame, p[4], p[6], Scalar(4, 20, 255), 2);
            line(frame, p[4], p[5], Scalar(4, 20, 255), 2);
            line(frame, p[5], p[7], Scalar(4, 20, 255), 2);
            line(frame, p[6], p[7], Scalar(4, 20, 255), 2);
            line(frame, p[0], p[4], Scalar(4, 20, 255), 2);
            line(frame, p[1], p[5], Scalar(4, 20, 255), 2);
            line(frame, p[2], p[6], Scalar(4, 20, 255), 2);
            line(frame, p[3], p[7], Scalar(4, 20, 255), 2);
}


vector<Vec3f> constructObjectCuboid() {
    
        vector<Vec3f> points;
        points.push_back(Vec3f(1, -1, 1));
        points.push_back(Vec3f(1, -4, 1));
        points.push_back(Vec3f(4, -1, 1));
        points.push_back(Vec3f(4, -4, 1));
        points.push_back(Vec3f(1, -1, 3));
        points.push_back(Vec3f(1, -4, 3));
        points.push_back(Vec3f(4, -1, 3));
        points.push_back(Vec3f(4, -4, 3));
        
    return points;
}

//Circle
vector<Vec3f> constructObjectCircle() {
    vector<Vec3f> objectPoints;
    objectPoints.push_back(Vec3f(2, -3, 2));
    for (float i = 0; i < 360; i += 5) {
        float x = 2 + cos(i * M_PI / 180);
        float z = 2 + sin(i * M_PI / 180);
        objectPoints.push_back(Vec3f(x, -3, z));
    }
    return objectPoints;
}


//sphere
vector<Vec3f> constructObjectSphere() {
    vector<Vec3f> objectPoints;
    int rings = 20;
    int segments = 35;
    float radius = 2;
    for (int i = 0; i <= rings; i++) {
        float phi = i * M_PI / rings;
        for (int j = 0; j <= segments; j++) {
            float theta = j * 2 * M_PI / segments;
            float x = radius * sin(phi) * cos(theta);
            float y = -radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);
            objectPoints.push_back(Vec3f(x+7, y-3, z+3));
        }
    }
    return objectPoints;
}


//All three together

vector<Vec3f> constructObjectAll() {


    vector<Vec3f> objectPoints;
    objectPoints.push_back(Vec3f(1, -1, 1));
    objectPoints.push_back(Vec3f(1, -4, 1));
    objectPoints.push_back(Vec3f(4, -1, 1));
    objectPoints.push_back(Vec3f(4, -4, 1));
    objectPoints.push_back(Vec3f(1, -1, 3));
    objectPoints.push_back(Vec3f(1, -4, 3));
    objectPoints.push_back(Vec3f(4, -1, 3));
    objectPoints.push_back(Vec3f(4, -4, 3));
    
    objectPoints.push_back(Vec3f(2, -3, 7));
    for (float i = 0; i < 360; i += 5) {
        float x = 2 + cos(i * M_PI / 180);
        float z = 2 + sin(i * M_PI / 180);
        objectPoints.push_back(Vec3f(x, -3, z+5));
    }

    int rings = 20;
    int segments = 35;
    float radius = 2;
    for (int i = 0; i <= rings; i++) {
        float phi = i * M_PI / rings;
        for (int j = 0; j <= segments; j++) {
            float theta = j * 2 * M_PI / segments;
            float x = radius * sin(phi) * cos(theta);
            float y = -radius * cos(phi);
            float z = radius * sin(phi) * sin(theta);
            objectPoints.push_back(Vec3f(x+7, y-3, z+3));
        }
    }
    return objectPoints;
}


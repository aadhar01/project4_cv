#ifndef PROJECT4_FUNCTIONS_H
#define PROJECT4_FUNCTIONS_H

using namespace std;
using namespace cv;



/*
 Generate vector<Vec3f> of the size given of the x and y coordinates
 */
vector<Vec3f> worldPoints(Size coorSize);

/*
function detects the corners of the chessboard object
return the vector of the Point2f of corners
*/
bool chessboardCorners2Vec(Mat &frame, Size patternSize, vector<Point2f> &corners);


void Matrix(Mat &matrix);


void Put4Corners(Mat &frame, vector<Vec3f> points, Mat rvec, Mat tvec, Mat cameraMatrix, Mat distCoeffs);

void createnProjectVO(Mat &frame, Mat rvec, Mat tvec, Mat cameraMatrix, Mat distCoeffs);

void projectObjects(Mat &frame, vector<Point2f> p);

vector<Vec3f> constructObjectCuboid();


vector<Vec3f> constructObjectCircle();

vector<Vec3f> constructObjectSphere();
vector<Vec3f> constructObjectAll();


#endif //
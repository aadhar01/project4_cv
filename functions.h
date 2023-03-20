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

/*
Function prints readable format of matrix.
Nested loop iterates through all elements.
Printing done in row-major order.
*/
void Matrix(Mat &matrix);

/*
Projects 3D points onto 2D image plane.
Draws circles on 4 specified corner points.
Uses camera parameters and distortion coefficients.
*/
void Put4Corners(Mat &frame, vector<Vec3f> points, Mat rvec, Mat tvec, Mat cameraMatrix, Mat distCoeffs);

/*
create a 3D object and project it onto a 2D image.
The specific object created can be changed by uncommenting lines.
The projected points are visualized as circles on the image.
*/
void createnProjectVO(Mat &frame, Mat rvec, Mat tvec, Mat cameraMatrix, Mat distCoeffs);

/*
Draws lines on an input frame.
Uses a vector of 2D points as input.
Lines are drawn based on the order of the points in the vector.
*/
void projectObjects(Mat &frame, vector<Point2f> p);


/*
Creates an 8-point vector for a cuboid.
Points are defined in 3D space.
Assumes cuboid is aligned with x, y, z axes.
*/
//Cuboid
vector<Vec3f> constructObjectCuboid();

/*
Generates a circular object using 360 points.
Points are evenly spaced around the circle.
Circle is centered at (2,-3,2).
*/
//Circle
vector<Vec3f> constructObjectCircle();


/*
Generates points for sphere with given parameters.
Uses spherical coordinates to calculate points.
Translates the sphere by a vector (7, -3, 3) to avoid overlap.
*/
//sphere
vector<Vec3f> constructObjectSphere();


//All three together Cuboid, Circle, Sphere
vector<Vec3f> constructObjectAll();


#endif //
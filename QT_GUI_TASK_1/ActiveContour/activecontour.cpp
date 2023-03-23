#include "activecontour.h"


// Function to calculate the internal energy term
double calcInternalEnergy(Point pt, Point prevPt, Point nextPt, double alpha) {
    double dx1 = pt.x - prevPt.x;
    double dy1 = pt.y - prevPt.y;
    double dx2 = nextPt.x - pt.x;
    double dy2 = nextPt.y - pt.y;
    double curvature = (dx1 * dy2 - dx2 * dy1) / pow(dx1*dx1 + dy1*dy1, 1.5);
    return alpha * curvature;
}

// Function to calculate the external energy term
double calcExternalEnergy(Mat img, Point pt, double beta) {
    return -beta * img.at<uchar>(pt.y, pt.x);
}

// Function to calculate the balloon energy term
double calcBalloonEnergy(Point pt, Point prevPt, double gamma) {
    double dx = pt.x - prevPt.x;
    double dy = pt.y - prevPt.y;
    return gamma * (dx*dx + dy*dy);
}

// Function to calculate the energy at a point on the curve
double calcEnergy(Mat img, Point pt, Point prevPt, Point nextPt, double alpha, double beta, double gamma) {
    double Einternal = calcInternalEnergy(pt, prevPt, nextPt, alpha);
    double Eexternal = calcExternalEnergy(img, pt, beta);
    double Eballoon = calcBalloonEnergy(pt, prevPt, gamma);
    return Einternal + Eexternal + Eballoon;
}

// Function to move the curve to minimize the energy function
void moveCurve(Mat img, vector<Point>& curve, double alpha, double beta, double gamma) {
    int numPoints = curve.size();  // example --> 10 points
    vector<Point> newCurve(numPoints);
    for (int i = 0; i < numPoints; i++) {
        //  5 6 7 8 9 0 1 2 3 4
        Point pt = curve[i];
        Point prevPt = curve[(i-1+numPoints)%numPoints];
        Point nextPt = curve[(i+1)%numPoints];
        double minEnergy = DBL_MAX; // max value can a double variable hold
        Point newPt = pt;
        // Try moving the point in different directions and choose the one with the minimum energy
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                Point movePt(pt.x + dx, pt.y + dy);
                double energy = calcEnergy(img, movePt, prevPt, nextPt, alpha, beta, gamma);
                if (energy < minEnergy) {
                    minEnergy = energy;
                    newPt = movePt;
                }
            }
        }
        newCurve[i] = newPt;
    }
    curve = newCurve;
}

// Function to run the Snake algorithm for a fixed number of iterations
void snake(Mat img, vector<Point>& curve, int numIterations, double alpha, double beta, double gamma) {
    // Convert image to grayscale
    Mat grayImg;
    Convert_To_Gray(img, grayImg);
    blur(grayImg, grayImg, Size(5,5));

    // Iterate for multiple iterations
    for (int i = 0; i < numIterations; i++) {
        moveCurve(grayImg, curve, alpha, beta, gamma);
    }
}

vector<Point> initial_contour(Point center, int radius){
     vector<Point> curve;

    for (int i = 0; i <= 360; i += 10) {
        double angle = i * CV_PI / 180;
        int x = center.x + radius * cos(angle);
        int y = center.y + radius * sin(angle);
        curve.push_back(Point(x, y));
    }

    return curve;
}

double points_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}


double contour_area(vector<Point> points, int n_points)
{
    double area = 0.0;
    // shoelace formula calculation:
    // 1/2 ((x1y2 + x2y3 + … + xn-1yn + xny1) – (x2y1 + x3y2 + … + xnyn-1 + x1yn))
    int j = n_points - 1;
    for (int i = 0; i < n_points; i++)
    {
        area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i;
    }
    return abs(area / 2.0);
}


double contour_perimeter(vector<Point> points, int n_points)
{
    double distance_sum = 0;
    for (int i = 0; i < n_points; i++)
    {
        int next_point = i + 1;
        if (i == n_points - 1)
        {
            next_point = 0;
        }

        double distance = points_distance(points[i].x, points[i].y, points[next_point].x, points[next_point].y);
        distance_sum += distance;
    }
    return distance_sum;
}

void display_area_perimeter(vector<Point> curve, Mat &outputImg){

    double area = contour_area(curve, curve.size());
    double perimeter = contour_perimeter(curve, curve.size());

    string string_area, string_perimeter;
    string_area = to_string(area);
    string_perimeter = to_string(perimeter);
    putText(outputImg, "area = "+ string_area, Point(5,15), FONT_HERSHEY_PLAIN, 1, Scalar(0,255,0), 1, false);
    putText(outputImg, "perimeter = " + string_perimeter, Point(5,35), FONT_HERSHEY_PLAIN, 1, Scalar(0,255,0), 1, false);

}


void active_Contour_Model(Mat img, Mat &outputImg, Point center, int radius, int numIterations, double alpha, double beta, double gamma){

    vector<Point> curve = initial_contour(center, radius);
    snake(img, curve, numIterations, alpha, beta, gamma);

    outputImg = img.clone();
    int i;
    for (i = 0; i < curve.size(); i++) {
        circle(outputImg, curve[i], 4, Scalar(0, 0, 255), -1);
        if (i > 0) {
            line(outputImg, curve[i-1], curve[i], Scalar(255, 0, 0), 2);
        }
    }
    line(outputImg, curve[0], curve[i-1], Scalar(255, 0, 0), 2);

    display_area_perimeter(curve,outputImg);

}

#ifndef ACTIVECONTOUR_H
#define ACTIVECONTOUR_H

#include "../Common.hpp"
#include <Filters/helper_functions.hpp>

double calcInternalEnergy(Point pt, Point prevPt, Point nextPt, double alpha);

double calcExternalEnergy(Mat img, Point pt, double beta);

double calcBalloonEnergy(Point pt, Point prevPt, double gamma);

double calcEnergy(Mat img, Point pt, Point prevPt, Point nextPt, double alpha, double beta, double gamma);

void moveCurve(Mat img, vector<Point>& curve, double alpha, double beta, double gamma);

void snake(Mat img, vector<Point>& curve, int numIterations, double alpha, double beta, double gamma);

vector<Point> initial_contour(Point center, int radius);

double points_distance(int x1, int y1, int x2, int y2);

double contour_area(vector<Point> points, int n_points);

double contour_perimeter(vector<Point> points, int n_points);

void display_area_perimeter(vector<Point> curve, Mat &outputImg);

void active_Contour_Model(Mat img, Mat &outputImg, Point center, int radius, int numIterations, double alpha, double beta, double gamma);


#endif // ACTIVECONTOUR_H

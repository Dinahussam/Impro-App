#ifndef HISTOGRAM
#define HISTOGRAM

#include "Common.hpp"
#include <QVector>


void calculate_histogram (Mat img_grayscale, map<int, int>& histo, vector<double>& cumulative_histo);

Mat normalize_image(Mat &image);

Mat Equalize_img(Mat &image);

vector<int> normalize_vector(vector <int> data);

void RGB_histo(Mat img, vector<double> barsPDF[6], vector<double> barsCDF[3]);

#endif

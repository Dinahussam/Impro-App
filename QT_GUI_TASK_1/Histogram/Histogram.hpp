#ifndef HISTOGRAM
#define HISTOGRAM

#include "Common.hpp"


void calculate_histogram (Mat img_grayscale, map<int, int>& histo, vector<int>& cumulative_histo);

Mat normalize_image(Mat &image);

Mat Equalize_img(Mat &image);

vector<int> normalize_vector(vector <int> data);
#endif

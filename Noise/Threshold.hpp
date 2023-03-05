#ifndef THRESHOLD
#define THRESHOLD

#include "../Common.hpp"

Mat global_threshold(Mat src, Mat dst, unsigned char threshold_value, unsigned char maximum_value = 255, unsigned char minimum_value = 0);

Mat local_adaptive_threshold(Mat src, Mat dst, unsigned char N_Of_Pixels = 5, unsigned char C = 2, unsigned char maximum_value = 255, unsigned char minimum_value = 0);

vector<int> local_threshold_mean_calculation(Mat src, unsigned char N_Of_Pixels = 5, unsigned char C = 2);

#endif
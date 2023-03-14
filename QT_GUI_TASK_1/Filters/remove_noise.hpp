#ifndef REMOVE_NOISE
#define REMOVE_NOISE

#include "Common.hpp"
#include "convolution.hpp"
#include"helper_functions.hpp"

Mat Gaussian_Filter(const Mat &src, int kernel_size = 3);

void Add_Median_Filter(const Mat &src, Mat &dst, int kernalSize);

void Add_Average_Filter(const Mat &src, Mat &dst, int kernalSize);


#endif

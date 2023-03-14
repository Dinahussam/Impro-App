#ifndef GAUSIAN
#define GAUSIAN

#include "../Common.hpp"
#include "convolution.hpp"

Mat Gaussian_Filter(const Mat &src, int kernel_size = 3);

Mat Gaussian_Filter_new(const Mat &src);


#endif

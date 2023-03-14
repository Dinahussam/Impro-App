#ifndef CONVOLUTION
#define CONVOLUTION

#include "../Common.hpp"
#include"helper_functions.hpp"




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

Mat transform_kernel(const Mat &src);

Mat Convolute_2d(const Mat &src, const Mat &kernel, int target_app = 1, int padding_margin = 1  , int data_type = UCHAR_FLAG );

Mat Convolute_2d_Mono(const Mat &src, const Mat &kernel, int target_app, int padding_margin , int data_type);

Mat Convolute_2d_RGB(const Mat &src, const Mat &kernel, int target_app, int padding_margin, int data_type);


#endif

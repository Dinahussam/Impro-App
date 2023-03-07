#ifndef FREQUENCY
#define FREQUENCY

#include "../Common.hpp"

void Add_Low_Frequency_Filter(const Mat &src, Mat &dst);

void Add_High_Frequency_Filter(const Mat &src, Mat &dst);

Mat Filter_Construction( Mat &scr, float Radius);

void fourier_shifting(const Mat &fourier_input_img, Mat &fourier_output_img);

void calculateDFT(Mat &scr, Mat &dst);

#endif
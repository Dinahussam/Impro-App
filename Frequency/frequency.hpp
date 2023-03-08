#ifndef FREQUENCY
#define FREQUENCY

#include "../Common.hpp"

void Add_Low_High_Frequency_Filter(const Mat &src, Mat &dst);

Mat Filter_Construction( Mat &scr, float Radius , float filter_flag);

Mat fourier_shifting(Mat &fourier_input_img);

void calculateDFT(Mat &scr, Mat &dst);

void Apply_Hybrid_Images(const Mat &src1 ,Mat &src2 , Mat &dst1 , Mat &dst2);


#endif
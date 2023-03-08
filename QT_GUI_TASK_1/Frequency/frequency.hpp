#ifndef FREQUENCY
#define FREQUENCY

#include "../Common.hpp"

Mat Filter_Construction( Mat &scr, float Radius , float filter_flag);

Mat fourier_shifting( Mat &fourier_input_img);

Mat Apply_Fourier_Transform( Mat &src);

Mat Apply_Shifting_to_Fourier_Img( Mat &src );

Mat Apply_Filtering( Mat &src, Mat shifted_DFT_real, Mat shifted_DFT_imaginary, float filterRadius, float flag);

Mat Inverse_Fourier_Transform( Mat &src);

Mat Add_Low_High_Frequency_Filter( Mat &src, float filterRadius , float flag);

Mat Apply_Hybrid_Images( Mat &src1 ,Mat &src2);

#endif

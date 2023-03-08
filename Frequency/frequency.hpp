#ifndef FREQUENCY
#define FREQUENCY

#include "../Common.hpp"

void Add_Low_Frequency_Filter(const Mat &src, Mat &dst);

Mat Apply_Shifting_to_Fourier_Img( Mat &src );

Mat Apply_Filtering( Mat &src, Mat shifted_DFT_real, Mat shifted_DFT_imaginary, float filterRadius, float flag);

Mat Inverse_Fourier_Transform( Mat &src);

Mat Add_Low_High_Frequency_Filter( Mat &src, float filterRadius , float flag);


#endif
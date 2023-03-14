#ifndef ADD_NOISE
#define ADD_NOISE

#include "../Common.hpp"
#include"helper_functions.hpp"


void Add_Gaussian_Noise(const Mat &src, Mat &dst, unsigned char gaussian_mean, unsigned char gaussian_STD, float noise_intensity);

void Add_Uniform_Noise(const Mat &src, Mat &dst, float noise_intensity);

void Add_Salt_And_Pepper_Noise(const Mat &src, Mat &dst, float salt_and_pepper_ammount);


#endif

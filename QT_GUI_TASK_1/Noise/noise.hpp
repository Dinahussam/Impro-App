#ifndef NOISE
#define NOISE

#include "../Common.hpp"

void Add_Gaussian_Noise(const Mat &src, Mat &dst, unsigned char gaussian_mean, unsigned char gaussian_STD, float noise_intensity);

void Add_Uniform_Noise(const Mat &src, Mat &dst, float noise_intensity);

void Convert_To_Gray(const Mat &src, Mat &dst);

void Add_Salt_And_Pepper_Noise(const Mat &src, Mat &dst, float salt_and_pepper_ammount);


#endif

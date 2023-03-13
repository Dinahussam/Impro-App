#ifndef REMOVE_NOISE
#define REMOVE_NOISE

#include "Common.hpp"
#include "Filters/convolution.hpp"


void Swap_Elements(unsigned char *first_element, unsigned char *second_element);

void Bubble_Sort(unsigned char array[], unsigned char size);

Mat Create_Kernel(int kernel_size, unsigned char *kernel_data, int image_type);

void Add_Median_Filter(const Mat &src, Mat &dst, int kernalSize);

void Add_Average_Filter(const Mat &src, Mat &dst, int kernalSize);

void Add_Gaussian_Filter(const Mat &src, Mat &dst, int kernalSize);


#endif

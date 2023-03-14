#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include "../Common.hpp"

void Convert_To_Gray(const Mat &src, Mat &dst);

void Swap_Elements(unsigned char *first_element, unsigned char *second_element);

void Bubble_Sort(unsigned char array[], unsigned char size);

Mat Create_Kernel(int kernel_size, unsigned char *kernel_data, int image_type);

Mat Padd_Mono(const Mat &src ,int padding_margin , int data_type = UCHAR_FLAG);

Mat Padd_RGB(const Mat &src ,int padding_margin);


#endif

#ifndef REMOVE_NOISE_H_
#define REMOVE_NOISE_H_

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Swap_Elements(unsigned char *first_element, unsigned char *second_element);
void Bubble_Sort(unsigned char array[], unsigned char size);
void Add_Median_Filter(const Mat &src, Mat &dst);

#endif
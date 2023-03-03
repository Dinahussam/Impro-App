#ifndef SOBEL
#define SOBEL

#include "../Common.hpp"
#include "convolution.hpp"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

Mat Detect_Edges_Sobel_X(const Mat &src);

Mat Detect_Edges_Sobel_Y(const Mat &src);

Mat Detect_Edges_Sobel(const Mat &src);

Mat Detect_Edges_Sobel_2(const Mat &src);

#endif

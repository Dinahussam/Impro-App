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

Mat Detect_Edges_Sobel_Magnitude_Gradient(const Mat &src);

Mat Detect_Edges_Sobel_Phase_Gradient(Mat &src);


#endif

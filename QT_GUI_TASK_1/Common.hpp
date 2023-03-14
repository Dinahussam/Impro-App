#ifndef COMMON_H
#define COMMON_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SOBEL_DETECTION     (1u)
#define PREWITT_DETECTION   (2u)
#define ROBERT_EDGE_DETECTION (1u)
#define GAUSSIAN_FILTER_3     (16u)
#define GAUSSIAN_FILTER_5     (273u)

#define UCHAR_FLAG 4
#define FLOAT_FLAG 16
#define WEAK_EDGE  40
#define STRONG_EDGE  255

using namespace cv;
using namespace std;

#endif

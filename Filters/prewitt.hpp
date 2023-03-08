#ifndef PREWITT
#define PREWITT

#include "../Common.hpp"
#include "convolution.hpp"

Mat Detect_Edges_Prewitt_X(const Mat &src);

Mat Detect_Edges_Prewitt_Y(const Mat &src);

Mat Detect_Edges_Prewitt(const Mat &src);


#endif

#ifndef ROBERT
#define ROBERT

#include "../Common.hpp"
#include "convolution.hpp"

Mat Robert_Edge(const Mat &src);

Mat Detect_Edges_Robert_X(const Mat &src);

Mat Detect_Edges_Robert_Y(const Mat &src);

Mat Detect_Edges_Robert(const Mat &src);

#endif

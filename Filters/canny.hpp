#ifndef CANNY
#define CANNY

#include "../Common.hpp"
#include "sobel.hpp"
#include "gaussian.hpp"

#define WEAK_EDGE  40
#define STRONG_EDGE  255

Mat Double_Threshoulding(Mat &suppressed, float lowThresholdRatio = 0.05, float highThresholdRatio = 0.09);

Mat Hysteresis (Mat &thresholded);

Mat Supression( Mat &magnitude_gradient,  Mat &phase_gradient);

Mat Detect_Edges_Canny( Mat &src);


#endif

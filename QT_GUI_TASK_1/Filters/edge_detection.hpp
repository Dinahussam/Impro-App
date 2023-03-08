#ifndef EDGE_DETECTION
#define EDGE_DETECTION

#include "convolution.hpp"
#include "gaussian.hpp"


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*************************************************************************************************
 ******************                        SOBEL                                  ****************
 *************************************************************************************************/

Mat Detect_Edges_Sobel_X(const Mat &src , int data_type = UCHAR_FLAG);

Mat Detect_Edges_Sobel_Y(const Mat &src ,int data_type = UCHAR_FLAG);

Mat Detect_Edges_Sobel(const Mat &src );

Mat Detect_Edges_Sobel_Magnitude_Gradient(const Mat &src);

Mat Detect_Edges_Sobel_Phase_Gradient(Mat &src);

/*************************************************************************************************
 ******************                        ROBERT                                  ****************
 *************************************************************************************************/

Mat Robert_Edge(const Mat &src);

Mat Detect_Edges_Robert_X(const Mat &src);

Mat Detect_Edges_Robert_Y(const Mat &src);

Mat Detect_Edges_Robert(const Mat &src);


/*************************************************************************************************
 ******************                        PREWITT                                  ****************
 *************************************************************************************************/

Mat Detect_Edges_Prewitt_X(const Mat &src);

Mat Detect_Edges_Prewitt_Y(const Mat &src);

Mat Detect_Edges_Prewitt(const Mat &src);

/*************************************************************************************************
 ******************                        CANNY                                  ****************
 *************************************************************************************************/

Mat Double_Threshoulding(Mat &suppressed, float lowThresholdRatio = 0.05, float highThresholdRatio = 0.09);

Mat Hysteresis (Mat &thresholded);

Mat Supression( Mat &magnitude_gradient,  Mat &phase_gradient);

Mat Detect_Edges_Canny(const Mat &src , float lowThresholdRatio = 0.05, float highThresholdRatio = 0.09);




#endif

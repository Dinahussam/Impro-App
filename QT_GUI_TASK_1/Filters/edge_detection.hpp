#ifndef EDGE_DETECTION
#define EDGE_DETECTION

#include "convolution.hpp"
#include "remove_noise.hpp"
#include"helper_functions.hpp"




/************************************************************************************************************
 *                                    Functions Prototypes                                                  *
 ************************************************************************************************************/

/*************************************************************************************************
 ******************                        Gradients                                  ************
 *************************************************************************************************/

Mat Magnitude_Gradient (const Mat &gradient_x , const Mat &gradient_y);

Mat Phase_Gradient (const Mat &gradient_x , const Mat &gradient_y);

/*************************************************************************************************
 ******************                        SOBEL                                  ****************
 *************************************************************************************************/

Mat Detect_Edges_Sobel_X(const Mat &src , int data_type = UCHAR_FLAG);

Mat Detect_Edges_Sobel_Y(const Mat &src ,int data_type = UCHAR_FLAG);

Mat Detect_Edges_Sobel(const Mat &src );

Mat Sobel_Phase_Gradient (const Mat &src);


/*************************************************************************************************
 ******************                        ROBERT                                  ****************
 *************************************************************************************************/

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

#define WEAK_EDGE  40
#define STRONG_EDGE  255

Mat Double_Threshoulding(Mat &suppressed, float lowThreshold, float highThreshold);

Mat Hysteresis (Mat &thresholded);

Mat Detect_Edges_Canny(const Mat &src , float lowThreshold, float highThreshold);

Mat Supression_Non_Max(Mat &magnitude_gradient, Mat &phase_gradient);


#endif

#ifndef CONVOLUTION
#define CONVOLUTION

#include "../Common.hpp"

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



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

Mat transform_kernel(const Mat &src);

Mat Padd_Mono(const Mat &src ,int padding_margin , int data_type = UCHAR_FLAG);

Mat Padd_RGB(const Mat &src ,int padding_margin);

Mat Convolute_2d(const Mat &src, const Mat &kernel, int target_app = 1, int padding_margin = 1  , int data_type = UCHAR_FLAG );

Mat Convolute_2d_Mono(const Mat &src, const Mat &kernel, int target_app, int padding_margin , int data_type);

Mat Convolute_2d_RGB(const Mat &src, const Mat &kernel, int target_app, int padding_margin, int data_type);


#endif

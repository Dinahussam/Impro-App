#include "edge_detection.hpp"

/************************************************************************************************************
 *                      Functions Definitions                                                               *
 ************************************************************************************************************/

/*************************************************************************************************
 ******************                        Gradients                                  ************
 *************************************************************************************************/

Mat Magnitude_Gradient(const Mat &gradient_x, const Mat &gradient_y)
{
    Mat Magnitude_Gradient = Mat::zeros(Size(gradient_x.cols, gradient_x.rows), gradient_x.type());
    for (int i = 0; i < gradient_x.rows; i++)
    {
        for (int j = 0; j < gradient_x.cols; j++)
        {
            Magnitude_Gradient.at<float>(i, j) = sqrt(pow(gradient_x.at<float>(i, j), 2) + pow(gradient_y.at<float>(i, j), 2));
        }
    }
    return Magnitude_Gradient;
}

/*****************************************************************************************************************************************/

Mat Phase_Gradient(const Mat &gradient_x, const Mat &gradient_y)
{
    Mat phase_gradient = Mat::zeros(Size(gradient_x.cols, gradient_y.rows), CV_32FC1);
    for (int i = 0; i < phase_gradient.rows; i++)
    {
        for (int j = 0; j < phase_gradient.cols; j++)
        {
            phase_gradient.at<float>(i, j) = atan2(gradient_y.at<float>(i, j), gradient_x.at<float>(i, j));
        }
    }
    phase_gradient = phase_gradient * 180 / M_PI;
    return phase_gradient;
}

/*************************************************************************************************
 ******************                        SOBEL                                  ****************
 *************************************************************************************************/

Mat Detect_Edges_Sobel_X(const Mat &src, int data_type)
{
    Mat sobel_x_kernel = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat Sobel_x;
    filter2D(src, Sobel_x, CV_32F, sobel_x_kernel);
    return Sobel_x;
}

/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel_Y(const Mat &src, int data_type)
{
    Mat sobel_y_kernel = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    Mat Sobel_y;
    filter2D(src, Sobel_y, CV_32F, sobel_y_kernel);
    return Sobel_y;
}

/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel(const Mat &src)
{
    Mat sobel_x = Detect_Edges_Sobel_X(src);
    Mat sobel_y = Detect_Edges_Sobel_Y(src);
    Mat sobel = Magnitude_Gradient(sobel_x, sobel_y);
    sobel.convertTo(sobel, CV_8U);
    return sobel;
}

/*****************************************************************************************************************************************/
Mat Sobel_Phase_Gradient(const Mat &src)
{
    Mat dst;
    Mat sobel_x = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat sobel_y = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    Mat sobel_x_32f, sobel_y_32f;
    filter2D(src, sobel_x_32f, CV_32F, sobel_x);
    filter2D(src, sobel_y_32f, CV_32F, sobel_y);
    phase(sobel_x_32f, sobel_y_32f, dst, true);
    return dst;
}

/*****************************************************************************************************************************************/

/*************************************************************************************************
 ******************                        ROBERT                                  ****************
 *************************************************************************************************/

Mat Detect_Edges_Robert_X(const Mat &src)
{
    Mat robert_x;
    Mat robert_x_kernel = (Mat_<float>(2, 2) << 1, 0, 0, -1);
    filter2D(src, robert_x, CV_32F, robert_x_kernel);
    return robert_x;
}

Mat Detect_Edges_Robert_Y(const Mat &src)
{
    Mat robert_y;
    Mat robert_y_kernel = (Mat_<float>(2, 2) << 0, 1, -1, 0);
    filter2D(src, robert_y, CV_32F, robert_y_kernel);
    return robert_y;
}

Mat Detect_Edges_Robert(const Mat &src)
{
    Mat robert_x = Detect_Edges_Robert_X(src);
    Mat robert_y = Detect_Edges_Robert_Y(src);
    Mat robert = Magnitude_Gradient(robert_x, robert_y);
    robert.convertTo(robert, CV_8U);
    return robert;
}

/*************************************************************************************************
 ******************                        PREWITT                                  ****************
 *************************************************************************************************/

Mat Detect_Edges_Prewitt_X(const Mat &src)
{
    float prewitt_x_data[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    Mat kernel_prewitt_x = Mat(3, 3, CV_32F, prewitt_x_data);

    Mat prewitt_x_img = Convolute_2d(src, kernel_prewitt_x, PREWITT_DETECTION, 1);
    return prewitt_x_img;
}

Mat Detect_Edges_Prewitt_Y(const Mat &src)
{
    float prewitt_y_data[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    Mat kernel_prewitt_y = Mat(3, 3, CV_32F, prewitt_y_data);

    Mat prewitt_y_img = Convolute_2d(src, kernel_prewitt_y, PREWITT_DETECTION, 1);
    return prewitt_y_img;
}

Mat Detect_Edges_Prewitt(const Mat &src)
{
    Mat prewitt_x_img = Detect_Edges_Prewitt_X(src);
    Mat prewitt_y_img = Detect_Edges_Prewitt_Y(src);
    Mat prewitt_img = prewitt_x_img + prewitt_y_img;
    return prewitt_img;
}

/*************************************************************************************************
 ******************                        CANNY                                  ****************
 *************************************************************************************************/

Mat Double_Threshoulding(Mat &suppressed, float lowThreshold , float highThreshold )
{
    Mat thresholded = Mat::zeros(Size(suppressed.cols, suppressed.rows), suppressed.type());

    for (int i = 0; i < suppressed.rows - 1; i++)
    {
        for (int j = 0; j < suppressed.cols - 1; j++)
        {
            if (suppressed.at<float>(i, j) > highThreshold)
            {
                thresholded.at<float>(i, j) = STRONG_EDGE;
            }
            else if ((suppressed.at<float>(i, j) < highThreshold) && (suppressed.at<float>(i, j) > lowThreshold))
            {
                thresholded.at<float>(i, j) = WEAK_EDGE;
            }
            else
            {
                thresholded.at<float>(i, j) = 0;
            }
        }
    }
    return thresholded;
}

Mat Hysteresis(Mat &thresholded)
{
    Mat hysteresis = thresholded.clone();
    for (int i = 1; i < thresholded.rows - 1; i++)
    {
        for (int j = 1; j < thresholded.cols - 1; j++)
        {
            if (thresholded.at<float>(i, j) == WEAK_EDGE)
            {
                if ((thresholded.at<float>(i + 1, j - 1) == STRONG_EDGE) || (thresholded.at<float>(i + 1, j) == STRONG_EDGE) || (thresholded.at<float>(i + 1, j + 1) == STRONG_EDGE) || (thresholded.at<float>(i, j - 1) == STRONG_EDGE) || (thresholded.at<float>(i, j + 1) == STRONG_EDGE) || (thresholded.at<float>(i - 1, j - 1) == STRONG_EDGE) || (thresholded.at<float>(i - 1, j) == STRONG_EDGE) || (thresholded.at<float>(i - 1, j + 1) == STRONG_EDGE))
                {
                    hysteresis.at<float>(i, j) = STRONG_EDGE;
                }
                else
                {
                    hysteresis.at<float>(i, j) = 0;
                }
            }
        }
    }
    return hysteresis;
}

Mat Supression_Non_Max(Mat &magnitude_gradient, Mat &phase_gradient)
{
    Mat suppressed = Mat::zeros(Size(magnitude_gradient.cols, magnitude_gradient.rows), magnitude_gradient.type());
    Mat angles = phase_gradient.clone();
    for (int i = 1; i < angles.rows - 1; i++)
    {
        for (int j = 1; j < angles.cols - 1; j++)
        {
            if (angles.at<float>(i, j) < 0)
            {
                angles.at<float>(i, j) = angles.at<float>(i, j) + 360;
            }
            // # 0 degrees
            if ((angles.at<float>(i, j) >= 337.5 || angles.at<float>(i, j) < 22.5) || (angles.at<float>(i, j) >= 157.5 && angles.at<float>(i, j) < 202.5))
            {
                if (magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i, j + 1) && magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i, j - 1))
                {
                    suppressed.at<float>(i, j) = magnitude_gradient.at<float>(i, j);
                }
            }
            // # 45 degrees
            if ((angles.at<float>(i, j) >= 22.5 && angles.at<float>(i, j) < 67.5) || (angles.at<float>(i, j) >= 202.5 && angles.at<float>(i, j) < 247.5))
            {
                if (magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i - 1, j + 1) && magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i + 1, j - 1))
                {
                    suppressed.at<float>(i, j) = magnitude_gradient.at<float>(i, j);
                }
            }
            // # 90 degrees
            if ((angles.at<float>(i, j) >= 67.5 && angles.at<float>(i, j) < 112.5) || (angles.at<float>(i, j) >= 247.5 && angles.at<float>(i, j) < 292.5))
            {
                if (magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i - 1, j) && magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i + 1, j))
                {
                    suppressed.at<float>(i, j) = magnitude_gradient.at<float>(i, j);
                }
            }
            // # 135 degrees
            if ((angles.at<float>(i, j) >= 112.5 && angles.at<float>(i, j) < 157.5) || (angles.at<float>(i, j) >= 292.5 && angles.at<float>(i, j) < 337.5))
            {
                if (magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i - 1, j - 1) && magnitude_gradient.at<float>(i, j) >= magnitude_gradient.at<float>(i + 1, j + 1))
                {
                    suppressed.at<float>(i, j) = magnitude_gradient.at<float>(i, j);
                }
            }
        }
    }
    return suppressed;
}

Mat Detect_Edges_Canny(const Mat &src, float lowThreshold, float highThreshold)
{
    Mat img = src.clone();

    // FIRST SMOOTH IMAGE
    Mat blurred = Gaussian_Filter(img);

    // THEN DETECT GRADIENTS
    Mat sobel_x = Detect_Edges_Sobel_X(blurred);
    Mat sobel_y = Detect_Edges_Sobel_Y(blurred);
    Mat magnitude_gradient = Magnitude_Gradient(sobel_x, sobel_y);
    Mat phase_gradient = Phase_Gradient(sobel_x, sobel_y);

    // THEN SUPRESS NON-MAXIMUM EDGES
    Mat suppressed = Supression_Non_Max(magnitude_gradient, phase_gradient);

    // THEN APPLY THRESHOLDING
    Mat thresholded = Double_Threshoulding(suppressed, lowThreshold, highThreshold);

    // THEN APPLY HYSTERESIS
    Mat canny_edges = Hysteresis(thresholded);

    // For steps visualization
    /*    // convert blured img to cv8u data type
       blurred.convertTo(blurred, CV_8U);

       namedWindow("blurred", WINDOW_AUTOSIZE);
       imshow("blurred", blurred);

       magnitude_gradient.convertTo(magnitude_gradient, CV_8U);
       phase_gradient.convertTo(phase_gradient, CV_8U);

       namedWindow("Sobel_Magnitude_Gradient", WINDOW_AUTOSIZE);
       imshow("Sobel_Magnitude_Gradient", magnitude_gradient);

       namedWindow("Sobel_Phase_Gradient", WINDOW_AUTOSIZE);
       imshow("Sobel_Phase_Gradient", phase_gradient);

       namedWindow("suppressed_before", WINDOW_AUTOSIZE);
       imshow("suppressed_before", suppressed);

       suppressed.convertTo(suppressed, CV_8U);

       namedWindow("suppressed", WINDOW_AUTOSIZE);
       imshow("suppressed", suppressed);

       thresholded.convertTo(thresholded, CV_8U);

       namedWindow("thresholded", WINDOW_AUTOSIZE);
       imshow("thresholded", thresholded);

       canny_edges.convertTo(canny_edges, CV_8U);

       namedWindow("hysteresis", WINDOW_AUTOSIZE);
       imshow("hysteresis", canny_edges); */

    canny_edges.convertTo(canny_edges, CV_8U);

    return canny_edges;
}

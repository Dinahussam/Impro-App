#include "edge_detection.hpp"


/********************************************************************************************
 *                      Functions Definitions                                               *
 *******************************************************************************************/


/*************************************************************************************************
 ******************                        SOBEL                                  ****************
 *************************************************************************************************/


Mat Detect_Edges_Sobel_X(const Mat &src , int data_type)
{
    float sobel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    Mat kernel_sobel_x = Mat(3, 3, CV_32F, sobel_x);
    Mat convoluted_x = Convolute_2d(src, kernel_sobel_x, SOBEL_DETECTION, 1, data_type);
    return convoluted_x;
}

/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel_Y(const Mat &src , int data_type )
{
    float sobel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    Mat kernel_sobel_y = Mat(3, 3, CV_32F, sobel_y);
    Mat convoluted_y = Convolute_2d(src, kernel_sobel_y, SOBEL_DETECTION, 1 , data_type);
    return convoluted_y;
}

/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel(const Mat &src)
{
    Mat sobel_x = Detect_Edges_Sobel_X(src);
    Mat sobel_y = Detect_Edges_Sobel_Y(src);
    Mat sobel = sobel_x + sobel_y;
    return sobel;
}


/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel_Magnitude_Gradient(const Mat &src)
{
    Mat sobel_x = Detect_Edges_Sobel_X(src);
    Mat sobel_y = Detect_Edges_Sobel_Y(src);
    Mat sobel = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), src.type());
    for (int i = 0; i < sobel.rows; i++)
    {
        for (int j = 0; j < sobel.cols; j++)
        {
            if (src.type() == 16)
            {
                // copy rgb to rgb
                for (int c = 0; c < 3; c++)
                {
                    sobel.at<Vec3b>(i, j)[c] = (uchar)sqrt(pow(sobel_x.at<Vec3b>(i, j)[c], 2) + pow(sobel_y.at<Vec3b>(i, j)[c], 2));
                }
            }
            else if (src.type() == 0)
            {
                sobel.at<uchar>(i, j) = sqrt(pow(sobel_x.at<uchar>(i, j), 2) + pow(sobel_y.at<uchar>(i, j), 2));
            }
            else
            {
                cout << "Error: Image type not supported" << endl;
                // return src;
            }
        }
    }
    return sobel;
}

/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel_Phase_Gradient(Mat &src)
{
    // Mat fImage;
    src.convertTo(src, CV_32FC1);

    Mat sobel_x = Detect_Edges_Sobel_X(src,FLOAT_FLAG);
    Mat sobel_y = Detect_Edges_Sobel_Y(src,FLOAT_FLAG);

    Mat phase_gradient = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), CV_32FC1);
    for (int i = 0; i < phase_gradient.rows; i++)
    {
        for (int j = 0; j < phase_gradient.cols; j++)
        {
            if (src.type() == 16)
            {
                    // Mat phase_gradient = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), CV_32FC3);
                // copy rgb to rgb
                for (int c = 0; c < 3; c++)
                {
                    phase_gradient.at<Vec3b>(i, j)[c] = (uchar)atan2(sobel_y.at<Vec3b>(i, j)[c], sobel_x.at<Vec3b>(i, j)[c]);
                }
            }
            else if ((src.type() == 0) || (src.type() == 5))
            {
                // Mat phase_gradient = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), src.type());
                phase_gradient.at<float>(i, j) = atan2(sobel_y.at<float>(i, j), sobel_x.at<float>(i, j));
                // sobel.at<uchar>(i, j) = (uchar)atan2(sobel_x.at<uchar>(i, j), sobel_y.at<uchar>(i, j));
            }
            else
            {
                cout << "Error: Image type not supported" << endl;
                // return src;
            }
        }
    }
    return phase_gradient;
}


/*************************************************************************************************
 ******************                        ROBERT                                  ****************
 *************************************************************************************************/

Mat Robert_Edge(const Mat &src)
{
    // float robert_data[4] = {1,0,0,-1};
    float robert_data[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};
    Mat robert_kernel = Mat(3, 3, CV_32F, robert_data);
    Mat convoluted = Convolute_2d(src, robert_kernel, 1, 2);
    return convoluted;
}

Mat Detect_Edges_Robert_X(const Mat &src)
{
    // float robert_data[4] = {1,0,0,-1};
    float robert_x_data[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};
    Mat robert_x_kernel = Mat(3, 3, CV_32F, robert_x_data);
    Mat robert_x = Convolute_2d(src, robert_x_kernel, 1, 2);
    return robert_x;
}

Mat Detect_Edges_Robert_Y(const Mat &src)
{
    // float robert_data[4] = {1,0,0,-1};
    float robert_y_data[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};
    Mat robert_y_kernel = Mat(3, 3, CV_32F, robert_y_data);
    Mat robert_y = Convolute_2d(src, robert_y_kernel, 1, 2);
    return robert_y;
}

Mat Detect_Edges_Robert(const Mat &src)
{
    Mat robert_x = Detect_Edges_Robert_X(src);
    Mat robert_y = Detect_Edges_Robert_Y(src);
    Mat robert = robert_x + robert_y;
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


Mat Double_Threshoulding(Mat &suppressed, float lowThreshold/*  = 0.05 */, float highThreshold /* = 0.09 */)
{
    Mat thresholded = Mat::zeros(Size(suppressed.cols, suppressed.rows), suppressed.type());

    // find the maximum value of the suppressed image
    double maxVal;
    minMaxLoc(suppressed, NULL, &maxVal, NULL, NULL);

    // float highThreshold = highThresholdRatio * maxVal;
    // float lowThreshold = highThreshold * lowThresholdRatio;

    // lowThreshold = 30;
    // highThreshold = 80;

    for (int i = 0; i < suppressed.rows - 1; i++)
    {
        for (int j = 0; j < suppressed.cols - 1; j++)
        {
            if (suppressed.at<uchar>(i, j) > highThreshold)
            {
                thresholded.at<uchar>(i, j) = STRONG_EDGE;
            }
            else if ((suppressed.at<uchar>(i, j) < highThreshold) && (suppressed.at<uchar>(i, j) > lowThreshold))
            {
                thresholded.at<uchar>(i, j) = WEAK_EDGE ;
            }
            else
            {
                thresholded.at<uchar>(i, j) = 0;
            }
        }
    }
    return thresholded;
}

Mat Hysteresis (Mat &thresholded)
{
    Mat hysteresis = thresholded.clone();
    for (int i = 1; i < thresholded.rows - 1; i++)
    {
        for (int j = 1; j < thresholded.cols - 1; j++)
        {
            if (thresholded.at<uchar>(i, j) == WEAK_EDGE)
            {
                if ( (thresholded.at<uchar>(i+1, j-1) == STRONG_EDGE) || (thresholded.at<uchar>(i+1, j) == STRONG_EDGE) || (thresholded.at<uchar>(i+1, j+1) == STRONG_EDGE) || (thresholded.at<uchar>(i, j-1) == STRONG_EDGE) || (thresholded.at<uchar>(i, j+1) == STRONG_EDGE) || (thresholded.at<uchar>(i-1, j-1) == STRONG_EDGE) || (thresholded.at<uchar>(i-1, j) == STRONG_EDGE) || (thresholded.at<uchar>(i-1, j+1) == STRONG_EDGE) )
                {
                    hysteresis.at<uchar>(i, j) = STRONG_EDGE;
                }
                else
                {
                    hysteresis.at<uchar>(i, j) = 0;
                }
            }
        }
    }
    return hysteresis;
}

Mat Supression( Mat &magnitude_gradient,  Mat &phase_gradient)
{
    Mat suppressed = Mat::zeros(Size(magnitude_gradient.cols, magnitude_gradient.rows), magnitude_gradient.type());

    // convert phase from radian to angles
    Mat angles = phase_gradient * 180 / M_PI;

    float neighbour_1 , neighbour_2;

    for (int i = 1; i < angles.rows-1; i++)
    {
        for (int j = 1; j < angles.cols-1; j++)
        {
            // angle 0
            if ( (angles.at<float>(i, j) < 22.5) || (angles.at<float>(i, j) >= 157.5 ) )
            {
                // cout << "hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" <<endl ;
                neighbour_1 = magnitude_gradient.at<uchar>(i, j+1);
                neighbour_2 = magnitude_gradient.at<uchar>(i, j-1);
            }
             // angle 45
            else if ( (angles.at<float>(i, j) >= 22.5) && (angles.at<float>(i, j) <= 67.5) )
            {
                neighbour_1 = magnitude_gradient.at<uchar>(i+1,j-1);
                neighbour_2 = magnitude_gradient.at<uchar>(i-1,j+1);           
            }
            // angle 90
            else if ( (angles.at<float>(i, j) >= 67.5) && (angles.at<float>(i, j) <112.5) )
            {
                neighbour_1 = magnitude_gradient.at<uchar>(i+1,j);
                neighbour_2 = magnitude_gradient.at<uchar>(i-1,j);
            }
            // angle 135
            else if ( (angles.at<float>(i, j) >= 112.5) && (angles.at<float>(i, j) < 157.5) )
            {
                neighbour_1 = magnitude_gradient.at<uchar>(i-1, j-1);
                neighbour_2 = magnitude_gradient.at<uchar>(i+1, j+1);
            }

            // check pixel with its neighbour pixels
            if ( (magnitude_gradient.at<uchar>(i, j) >= neighbour_1) && (magnitude_gradient.at<uchar>(i, j) >= neighbour_2))
            {
                suppressed.at<uchar>(i, j) = magnitude_gradient.at<uchar>(i, j);
            }
            else
            {
                suppressed.at<uchar>(i, j) = 0;
            }
            
        }
    }
    return suppressed;
}


Mat Detect_Edges_Canny( const Mat &src,  float lowThresholdRatio /* = 0.05 */, float highThresholdRatio /* 0.09 */ ) 
{
    // FIRST SMOOTH IMAGE
    Mat blurred = Gaussian_Filter_new(src);
    cout << "****************************** After blur ****************************" << endl;

    // THEN calculate sobel magnitude and phase gradients
    Mat magnitude_gradient = Detect_Edges_Sobel_Magnitude_Gradient(blurred);

    Mat phase_gradient = Detect_Edges_Sobel_Phase_Gradient(blurred);

    // THEN SUPRESS NON-MAXIMUM EDGES
    Mat suppressed = Supression(magnitude_gradient, phase_gradient);

    // THEN APPLY THRESHOLDING
    Mat thresholded = Double_Threshoulding(suppressed,lowThresholdRatio,highThresholdRatio);

    // THEN APPLY HYSTERESIS
    Mat canny_edges = Hysteresis(thresholded);


    // namedWindow("blurred", WINDOW_AUTOSIZE);
    // imshow("blurred", blurred);

    // namedWindow("Sobel_Magnitude_Gradient", WINDOW_AUTOSIZE);
    // imshow("Sobel_Magnitude_Gradient", magnitude_gradient);

    // namedWindow("Sobel_Phase_Gradient", WINDOW_AUTOSIZE);
    // imshow("Sobel_Phase_Gradient", phase_gradient);

    // namedWindow("suppressed", WINDOW_AUTOSIZE);
    // imshow("suppressed", suppressed);

    // namedWindow("thresholded", WINDOW_AUTOSIZE);
    // imshow("thresholded", thresholded);

    // namedWindow("hysteresis", WINDOW_AUTOSIZE);
    // imshow("hysteresis", canny_edges);

    return canny_edges;
}

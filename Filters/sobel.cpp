#include "sobel.hpp"

/********************************************************************************************
 *                      Functions Definitions                                               *
 *******************************************************************************************/

Mat Detect_Edges_Sobel_X(const Mat &src)
{
    float sobel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    Mat kernel_sobel_x = Mat(3, 3, CV_32F, sobel_x);
    Mat convoluted_x = Convolute_2d(src, kernel_sobel_x, SOBEL_DETECTION, 1);
    return convoluted_x;
}

/*****************************************************************************************************************************************/

Mat Detect_Edges_Sobel_Y(const Mat &src)
{
    float sobel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    Mat kernel_sobel_y = Mat(3, 3, CV_32F, sobel_y);
    Mat convoluted_y = Convolute_2d(src, kernel_sobel_y, SOBEL_DETECTION, 1);
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
                sobel.at<uchar>(i, j) = sqrt(pow(sobel_x.at<float>(i, j), 2) + pow(sobel_y.at<float>(i, j), 2));
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

Mat Detect_Edges_Sobel_Phase_Gradient(const Mat &src)
{
    Mat sobel_x = Detect_Edges_Sobel_X(src);
    Mat sobel_y = Detect_Edges_Sobel_Y(src);

    Mat phase_gradient = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), CV_64FC1);
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
            else if (src.type() == 0)
            {
                // Mat phase_gradient = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), CV_32FC1);
                phase_gradient.at<double>(i, j) = atan2(sobel_y.at<float>(i, j), sobel_x.at<float>(i, j));
                // sobel.at<uchar>(i, j) = (uchar)atan2(sobel_x.at<uchar>(i, j), sobel_y.at<uchar>(i, j));

            }
            else
            {
                cout << "Error: Image type not supported" << endl;
                // return src;
            }
        }
    }
    // print sobel
    // cout << sobel << endl;
    return phase_gradient;
}
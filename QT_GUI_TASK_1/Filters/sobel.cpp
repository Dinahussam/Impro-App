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

Mat Detect_Edges_Sobel_2(const Mat &src)
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
                sobel.at<uchar>(i, j) = (uchar)sqrt(pow(sobel_x.at<uchar>(i, j), 2) + pow(sobel_y.at<uchar>(i, j), 2));
            }
            else
            {
                cout << "Error: Image type not supported" << endl;
                // return src;
            }
        }
    }
    // Mat sobel = pow(sobel_x,2) + pow(sobel_y,2);
    // sobel = sqrt(sobel);
    // Mat sobel = cv.bitw
    return sobel;
}

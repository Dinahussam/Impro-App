#include "Thresholding.hpp"

Mat global_threshold(Mat src, Mat dst, unsigned char threshold_value, unsigned char maximum_value /* = 255 */, unsigned char minimum_value /* = 0 */)
{
    for (int row = 0; row < src.rows; row++)
    {
        for (int col = 0; col < src.cols; col++)
        {
            if (src.at<uchar>(row, col) >= threshold_value)
            {
                dst.at<uchar>(row, col) = maximum_value;
            }
            else
            {
                dst.at<uchar>(row, col) = minimum_value;
            }
        }
    }
    return dst;
}

Mat local_adaptive_threshold(Mat src, Mat dst, unsigned char kernal_size /* = 4 */, unsigned char C /* = 2 */, unsigned char maximum_value /* = 255 */, unsigned char minimum_value /* = 0 */)
{
    vector<int> mean_values = local_threshold_mean_calculation(src);

    int mean_operator = 0;
    int row = 0, col = 0, i = 0, j = 0;

    while (row < src.rows && col < src.cols)
    {
        i = row;
        while (i < kernal_size + row)
        {
            j = col;
            while (j < kernal_size + col)
            {
                if (src.at<uchar>(i, j) >= mean_values[mean_operator])
                {
                    dst.at<uchar>(i, j) = maximum_value;
                }
                else
                {
                    dst.at<uchar>(i, j) = minimum_value;
                }

                j++;
            }
            i++;
        }
        row = row + kernal_size;
        mean_operator++;

        if (row == src.rows && col != src.cols)
        {
            row = 0;
            col = col + kernal_size;
        }
    }
    return dst;
}

vector<int> local_threshold_mean_calculation(Mat src, unsigned char kernal_size /* = 4 */, unsigned char C /* = 2 */)
{

    int row = 0, col = 0, i = 0, j = 0;

    int pixel_summation = 0;
    int adaptive_thresh_mean = 0;

    vector<int> mean_values;

    while (row < src.rows && col < src.cols)
    {
        i = row;
        pixel_summation = 0;

        while (i < kernal_size + row)
        {
            j = col;
            while (j < kernal_size + col)
            {
                pixel_summation = pixel_summation + src.at<uchar>(i, j);
                j++;
            }
            i++;
        }

        row = row + kernal_size;

        if (row == src.rows && col != src.cols)
        {
            row = 0;
            col = col + kernal_size;
        }

        adaptive_thresh_mean = (pixel_summation / (kernal_size * 2)) - C;
        mean_values.push_back(adaptive_thresh_mean);
    }

    return mean_values;
}



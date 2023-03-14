#include "Thresholding.hpp"
#include "Filters/convolution.hpp"

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

Mat local_adaptive_threshold(Mat src, Mat dst, unsigned char kernal_size /* = 3 */, unsigned char C /* = 2 */, unsigned char maximum_value /* = 255 */, unsigned char minimum_value /* = 0 */)
{

    Mat mean_window = local_threshold_mean_calculation(src, 9, C);

    for (int i = 0; i < src.rows; i++)
    {
        for (int  j = 0; j < src.cols; j++)
        {
                if (src.at<uchar>(i, j) >= mean_window.at<uchar>(i, j))
                {
                    dst.at<uchar>(i, j) = maximum_value;
                }
                else
                {
                    dst.at<uchar>(i, j) = minimum_value;
                }
        }
    }

    return dst;
}

Mat adaptive_padding_function(Mat src){

    Mat dst;
    dst = Padd_Mono(src, 1);

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if( i == 0  && j == 0 ) {
                dst.at<uchar>(i, j) = src.at<uchar>(i, j);
            }
            if(i == src.rows - 1 && j == src.cols - 1){
                dst.at<uchar>(i + 2, j + 2) = src.at<uchar>(i, j);
            }
            if(i == 0 &&  j == src.cols - 1){
                dst.at<uchar>(i , j + 2) = src.at<uchar>(i, j);
            }
            if(i == src.rows - 1 && j == 0){
                dst.at<uchar>(i + 2 , j) = src.at<uchar>(i, j);
            }
            if( i == 0 ){
                dst.at<uchar>(i , j + 1) = src.at<uchar>(i, j);
            }
            if ( j == 0 ){
                dst.at<uchar>(i + 1, j) = src.at<uchar>(i, j);
            }
            if( j == src.cols - 1){
                dst.at<uchar>(i + 1, j + 2) = src.at<uchar>(i, j);
            }
            if( i == src.rows - 1){
                dst.at<uchar>(i + 2 , j + 1) = src.at<uchar>(i, j);
            }
        }
    }

    return dst;
}

Mat local_threshold_mean_calculation(const Mat &src, int target_app, int C)
{
    vector<int> mean_values;
    Mat padded_img = adaptive_padding_function(src);
    Mat convoluted_img = Mat::zeros(Size(src.cols, src.rows), src.type());

    float window_values[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Mat mean_window = Mat(3, 3, CV_32F, window_values);

    int h = mean_window.rows / 2;
    int w = mean_window.cols / 2;

    float window_sum;
    // convolute image
    for (int i = 1; i < (padded_img.rows - 1); i++)
    {
        for (int j = 1; j < (padded_img.cols - 1); j++)
        {
            window_sum = 0;
            for (int m = 0; m < mean_window.rows; m++)
            {
                for (int n = 0; n < mean_window.cols; n++)
                {
                    window_sum += padded_img.at<uchar>(i + m - h, j + n - w) * mean_window.at<float>(m, n);

                }
            }
            convoluted_img.at<uchar>(i - 1, j - 1) = window_sum/target_app - C;

        }
    }
    return convoluted_img;
}












//    while (row < src.rows && col < src.cols)
//    {
//        i = row;
//        pixel_summation = 0;

//        while (i < kernal_size + row)
//        {
//            j = col;
//            while (j < kernal_size + col)
//            {
//                pixel_summation = pixel_summation + src.at<uchar>(i, j);
//                j++;
//            }
//            i++;
//        }

//        row = row + kernal_size;

//        if (row == src.rows && col != src.cols)
//        {
//            row = 0;
//            col = col + kernal_size;
//        }

//        adaptive_thresh_mean = (pixel_summation / (kernal_size * 2)) - C;
//        mean_values.push_back(adaptive_thresh_mean);
//    }

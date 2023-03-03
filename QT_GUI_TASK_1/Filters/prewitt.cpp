#include "prewitt.hpp"

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

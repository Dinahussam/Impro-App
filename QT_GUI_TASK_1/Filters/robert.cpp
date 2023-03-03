#include "robert.hpp"

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

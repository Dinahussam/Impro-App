#include "robert.hpp"

Mat Robert_Edge(const Mat &src)
{
    // float robert_data[4] = {1,0,0,-1};
    float robert_data[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};
    Mat robert_kernel = Mat(3, 3, CV_32F, robert_data);
    Mat convoluted = Convolute_2d_Mono(src, robert_kernel, 1, 2);
    return convoluted;
}
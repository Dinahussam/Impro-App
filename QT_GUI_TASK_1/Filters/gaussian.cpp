#include "gaussian.hpp"


Mat Gaussian_Filter(const Mat &src)
{

    // float gaussian_data[9] = {1,2,1,2,4,2,1,2,1};
    float gaussian_data[25] = {1,4,7,4,1,4,16,26,16,4,7, 26, 41, 26, 7,4,16,26,16,4, 1,4,7,4,1};
    Mat gaussian_kernel = Mat(5, 5, CV_32F, gaussian_data);

            Mat convoluted = Convolute_2d(src, gaussian_kernel,GAUSSIAN_FILTER_5,2);
        return convoluted;

}
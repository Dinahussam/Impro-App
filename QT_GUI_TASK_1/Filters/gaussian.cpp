#include "gaussian.hpp"

Mat Gaussian_Filter(const Mat &src, int kernel_size)
{

    if (kernel_size == 3)
    {
        float gaussian_data[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
        Mat gaussian_kernel = Mat(3, 3, CV_32F, gaussian_data);
        Mat blurred = Convolute_2d(src, gaussian_kernel, GAUSSIAN_FILTER_3, 1);
        return blurred;
    }
    else if (kernel_size == 5)
    {
    float gaussian_data[25] = {1, 4, 7, 4, 1, 4, 16, 26, 16, 4, 7, 26, 41, 26, 7, 4, 16, 26, 16, 4, 1, 4, 7, 4, 1};
    Mat gaussian_kernel = Mat(5, 5, CV_32F, gaussian_data);
    Mat blurred = Convolute_2d(src, gaussian_kernel, GAUSSIAN_FILTER_5, 2);
    return blurred;
    }
    else
    {
        cout << "Invalid kernel size" << endl;
        return src;
    }
}

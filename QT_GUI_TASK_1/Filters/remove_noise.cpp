#include "remove_noise.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*---------------------------------- Gaussian filter ----------------------------------*/
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




/*---------------------------------- Median filter ----------------------------------*/

void Add_Median_Filter(const Mat &src, Mat &dst, int kernalSize)
{
    int ctr=0;
    int padding = kernalSize/2;
    int windowSize = kernalSize*kernalSize;
    int medianIndex = (windowSize-1)/2;

    src.copyTo(dst);

    unsigned char window[windowSize];
    for (int row = padding; row < src.rows - padding; row++)
    {
        for (int col = padding; col < src.cols - padding; col++)
        {
            ctr = 0;
            for(int i = row - padding; i <= row + padding; i++){

                for(int j = col - padding; j<= col + padding; j++){

                    window[ctr] = src.at<uchar>(i,j);
                    ctr++;
                }
            }
            Bubble_Sort(window, windowSize);

            unsigned char median = window[medianIndex];

            dst.at<uchar>(row, col) = median;
        }
    }
}

/*---------------------------------- Average filter ----------------------------------*/

void Add_Average_Filter(const Mat &src, Mat &dst, int kernalSize)
{

    src.copyTo(dst);
    cout << src.rows << endl;
    cout << src.cols << endl;
    for (int i = 0; i < src.rows - kernalSize; i++)
    {
        for (int j = 0; j < src.cols - kernalSize; j++)
        {
            Scalar intensity1 = 0;
            Scalar intensity2;
            for (int p = 0; p < kernalSize; p++)
            {
                for (int q = 0; q < kernalSize; q++)
                {
                    intensity1 = src.at<uchar>(i + p, j + q);
                    intensity2.val[0] += intensity1.val[0];
                }
            }
            dst.at<uchar>(i + (kernalSize - 1) / 2, j + (kernalSize - 1) / 2) = intensity2.val[0] / (kernalSize * kernalSize);
        }
    }
}


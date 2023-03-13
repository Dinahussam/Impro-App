#include "remove_noise.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*------------------------------- Helper Functions -----------------------------------*/

void Swap_Elements(unsigned char *first_element, unsigned char *second_element)
{
    unsigned char temp = *first_element;
    *first_element = *second_element;
    *second_element = temp;
}

void Bubble_Sort(unsigned char array[], unsigned char size)
{
    int first_index, second_index;
    for (first_index = 0; first_index < size - 1; first_index++)
        for (second_index = 0; second_index < size - first_index - 1; second_index++)
            if (array[second_index] > array[second_index + 1])
                Swap_Elements(&array[second_index], &array[second_index + 1]);
}

Mat Create_Kernel(int kernel_size, unsigned char *kernel_data, int image_type)
{
    Mat kernel = Mat::zeros(Size(kernel_size, kernel_size), image_type);
    int data_index = 0;
    cout << "-------------" << endl;
    for (int row = 0; row < kernel_size; row++)
    {
        for (int col = 0; col < kernel_size; col++)
        {
            kernel.at<uchar>(row, col) = kernel_data[data_index];
            data_index++;
        }
    }
    cout << data_index << endl;
    return kernel;
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


/*---------------------------------- Gaussian filter ----------------------------------*/

void Add_Gaussian_Filter(const Mat &src, Mat &dst, int kernalSize)
{

    unsigned char kernel_data[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

    Mat gaussian_kernel = Create_Kernel(3, kernel_data, 0);
    cout << gaussian_kernel << endl;

    dst = Convolute_2d(src, gaussian_kernel,1,1);
    cout << gaussian_kernel << endl;
}

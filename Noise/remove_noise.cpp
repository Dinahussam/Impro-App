#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

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

void Add_Median_Filter(const Mat &src, Mat &dst)
{
    unsigned char window[9];

    src.copyTo(dst);

    for (int row = 1; row < src.rows-1 ; row++)
    {
        for (int col = 1; col < src.cols-1; col++)
        {
            window[0] = src.at<uchar>(row-1, col-1);
            window[1] = src.at<uchar>(row-1, col);
            window[2] = src.at<uchar>(row-1, col+1);
            window[3] = src.at<uchar>(row, col-1);
            window[4] = src.at<uchar>(row, col);
            window[5] = src.at<uchar>(row, col+1);
            window[6] = src.at<uchar>(row+1, col-1);
            window[7] = src.at<uchar>(row+1, col);
            window[8] = src.at<uchar>(row+1, col+1); 

            Bubble_Sort(window, 9);

            unsigned char median = window[4];

            dst.at<uchar>(row, col) = median;
        }   
    }
}
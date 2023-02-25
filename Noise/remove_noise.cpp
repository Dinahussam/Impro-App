#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


/*------------------------------- Median filter -----------------------------------*/

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


/*---------------------------------- Average filter ----------------------------------*/


void Add_Average_Filter(const Mat &src, Mat &dst)
    {
       src.copyTo(dst);
       cout << src.rows << endl;
       cout << src.cols << endl;
        for (int i = 0; i < src.rows-3; i++) 
        { 
            for (int j = 0; j < src.cols-3; j++) 
            { 
                 Scalar intensity1 = 0;
                 Scalar intensity2 ;
             for (int p = 0; p<3; p++) 
                { 
            
                for (int q = 0; q<3; q++) 
                    { 
                        intensity1 = src.at<uchar>(i+p,j+q); 
                        intensity2.val[0] +=intensity1.val[0];
                    }
                }
            dst.at<uchar>(i+(3-1)/2,j+(3-1)/2)=intensity2.val[0]/(3*3);
            
            } 
        }
    }
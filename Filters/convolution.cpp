#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat transform_kernel(const Mat &src){

    Mat transformed_kernel = Mat::zeros(Size(src.rows,src.cols),src.type());
    for (int i = 0 ; i<src.rows ; i++)
    {
        for (int j = 0 ; j<src.cols ; j++)
        {
            transformed_kernel.at<float>(i,j) = src.at<float>(src.rows-1-i,src.cols-1-j);
        }
    }
    return transformed_kernel;
}


void Padd_Image(const Mat &src){
    Mat padding_img = Mat::zeros(Size(src.rows+2,src.cols+2),src.type());

    // Padding ----------------------------------------------------
    for( int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {
            // copy rgb to rgb
            for(int c=0; c<3; c++)
            {
                padding_img.at<Vec3b>(i+1,j+1)[c] = src.at<Vec3b>(i,j)[c];
            }
        }
    }
    return padding_img
}
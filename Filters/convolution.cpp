#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat transform_kernel(const Mat &src){

    Mat transformed_kernel = Mat::zeros(Size(src.cols,src.rows),src.type());
    // cout <<src.type() << endl;
    for (int i = 0 ; i<src.rows ; i++)
    {
        for (int j = 0 ; j<src.cols ; j++)
        {
            transformed_kernel.at<float>(i,j) = src.at<float>(src.rows-1-i,src.cols-1-j);
        }
    }
    return transformed_kernel;
}

Mat Padd_Mono(const Mat &src){
    Mat padding_img = Mat::zeros(Size(src.cols+2,src.rows+2),src.type());

    // Padding ----------------------------------------------------
    for( int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {
            // copy rgb to rgb
            // for(int c=0; c<3; c++)
            // {
                // padding_img.at<Vec3b>(i+1,j+1)[c] = src.at<Vec3b>(i,j)[c];
            padding_img.at<uchar>(i+1,j+1) = src.at<uchar>(i,j);

            // }
        }
    }
    return padding_img;
}

Mat Padd_RGB(const Mat &src){
    Mat padding_img = Mat::zeros(Size(src.cols+2,src.rows+2),src.type());
    cout<< "Padded size: " << padding_img.size() << endl;

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
    return padding_img;
}


Mat Convolute_2d_Mono(const Mat &src , const Mat &kernel)
{
    Mat padded_img = Padd_Mono(src);

    Mat new_kernel =  transform_kernel(kernel);

    Mat convoluted_img = Mat::zeros(Size(src.cols,src.rows),src.type());

    float conv_sum;
// convolute image
    for (int i =1;i<padded_img.rows-1 ; i++)
    {
        for (int j = 1 ; j<padded_img.cols-1 ; j++)
        {
            conv_sum = 0;
            for(int m = 0 ; m<3;m++ )
            {
                for(int n = 0 ; n<3 ; n++)
                {
                    conv_sum += padded_img.at<uchar>(i+m-1,j+n-1) * new_kernel.at<float>(m,n);
                }
            }
            // absolute of conv_sum
            conv_sum = abs(conv_sum);
            convoluted_img.at<uchar>(i-1,j-1) = (int)conv_sum;
        }
    }
    return convoluted_img;
}

Mat Convolute_2d_RGB(const Mat &src , const Mat &kernel)
{
    Mat padded_img = Padd_RGB(src);

    Mat new_kernel =  transform_kernel(kernel);

    Mat convoluted_img = Mat::zeros(Size(src.cols,src.rows),src.type());

    float conv_sum_r,conv_sum_g,conv_sum_b;
// convolute image
    for (int i =1;i<padded_img.rows-1 ; i++)
    {
        for (int j = 1 ; j<padded_img.cols-1 ; j++)
        {
            conv_sum_r = 0;
            conv_sum_g = 0;
            conv_sum_b = 0;
            for(int m = 0 ; m<3;m++ )
            {
                for(int n = 0 ; n<3 ; n++)
                {
                    conv_sum_r += padded_img.at<Vec3b>(i+m-1,j+n-1)[0] * new_kernel.at<float>(m,n);
                    conv_sum_g += padded_img.at<Vec3b>(i+m-1,j+n-1)[1] * new_kernel.at<float>(m,n);
                    conv_sum_b += padded_img.at<Vec3b>(i+m-1,j+n-1)[2] * new_kernel.at<float>(m,n);
                }
            }
            // absolute of conv_sum
            conv_sum_r = abs(conv_sum_r);
            conv_sum_g = abs(conv_sum_g);
            conv_sum_b = abs(conv_sum_b);

            convoluted_img.at<Vec3b>(i-1,j-1)[0] = (int)conv_sum_r;
            convoluted_img.at<Vec3b>(i-1,j-1)[1] = (int)conv_sum_g;
            convoluted_img.at<Vec3b>(i-1,j-1)[2] = (int)conv_sum_b;
        }
    }
    return convoluted_img;
}

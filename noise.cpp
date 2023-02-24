#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void Add_Gaussian_Noise(const Mat &src, Mat &dst, unsigned char gaussian_mean, unsigned char gaussian_STD, float noise_intensity){
    Mat noisy_image = Mat::zeros(src.rows, src.cols, 0);
    //  Set the pixel values as a Gaussian noise by setting the mean value and standard deviation
    randn(noisy_image, gaussian_mean, gaussian_STD);
    dst = src.clone();
    dst = src + noisy_image*noise_intensity;
}



void adjust_threshold (Mat src, Mat dst, unsigned char threshold_value, unsigned char maximum_value = 255, unsigned char minimum_value = 0){
    for (int row = 0; row < src.rows; row++)
    {
        for (int col = 0; col < src.cols; col++)
        {
            if(src.at<uchar>(row,col) >= threshold_value){
                dst.at<uchar>(row,col)=255;
            }
            else{
                dst.at<uchar>(row,col)=0;
            }    
        }      
    }   
}

void Add_Uniform_Noise(const Mat &src, Mat &dst, unsigned char threshold_value, float noise_intensity){
    Mat noisy_image = Mat::zeros(src.rows, src.cols, 0);
    randu(noisy_image, 0, 255);
    dst = src.clone();
    adjust_threshold(src, dst, threshold_value);
    dst = src + noisy_image*noise_intensity; 
}



void Convert_To_Gray(const Mat &src, Mat &dst)
{
    int rows = src.rows, cols = src.cols;

    dst.create(src.size(), 0);

    cols = rows * cols;
    rows = 1;

    for (int row = 0; row < rows; row++)
    {
        const uchar* src_ptr = src.ptr<uchar>(row);
        uchar* dst_ptr = dst.ptr<uchar>(row);

        for (int col = 0; col < cols; col++)
        {
            dst_ptr[col] = (uchar)(src_ptr[0] * 0.114f + src_ptr[1] * 0.587f + src_ptr[2] * 0.299f);
            src_ptr += 3;
        }
    }
}

void Add_Salt_And_Pepper_Noise(const Mat &src, Mat &dst, float salt_and_pepper_ammount){
    float random;
    float pepper = salt_and_pepper_ammount;
    float salt = 1-pepper;

    dst = src.clone();

    for (int row = 0; row < dst.rows; row++)
    {
        for (int col = 0; col < dst.cols; col++)
        {
            random = (float) rand()/RAND_MAX;
            if (random < pepper){
                dst.at<uchar>(row, col) = 0;
            }
            else if (random > salt){
                dst.at<uchar>(row, col) = 255;
            }
        }   
    }    
}
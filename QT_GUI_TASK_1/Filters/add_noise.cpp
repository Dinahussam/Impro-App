#include "add_noise.hpp"


void Add_Gaussian_Noise(const Mat &src, Mat &dst, unsigned char gaussian_mean, unsigned char gaussian_STD, float noise_intensity){
    Mat noisy_image = Mat::zeros(src.rows, src.cols, 0);
    //  Set the pixel values as a Gaussian noise by setting the mean value and standard deviation
    randn(noisy_image, gaussian_mean, gaussian_STD);
    dst = src.clone();
    dst = src + noisy_image*noise_intensity;
}




void Add_Uniform_Noise(const Mat &src, Mat &dst, float noise_intensity){
    Mat noisy_image = Mat::zeros(src.rows, src.cols, 0);
    randu(noisy_image, 0, 255);
    dst = src.clone();
    dst = src + noisy_image*noise_intensity; 
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

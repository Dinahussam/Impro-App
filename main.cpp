#include "Noise/noise.hpp"
#include "Noise/remove_noise.hpp"

#include "Filters/sobel.hpp"
#include "Filters/gaussian.hpp"
#include "Filters/prewitt.hpp"
#include "Filters/robert.hpp"

#include "Frequency/frequency.hpp"

int main()
{
    Mat image;
    Mat image2;
    Mat image3;
    Mat AvgFilterImg;
    Mat GaussianFilterImg;


    Mat InversImg;
    Mat fourier_output_img;
    Mat fourierImg;

    Mat src1;
    Mat src2;
    Mat Hybrid_low ;
    Mat Hybrid_High;

// --------------------------------------- Img Read ---------------------------------------
    // image = imread("C:\\Users\\HP Probook\\Documents\\GitHub\\CV_task1_team15\\Images\\sudoku.png");

    src1 = imread("C:\\Users\\HP Probook\\Documents\\GitHub\\CV_task1_team15\\Images\\lenna.png");
    src2 = imread("C:\\Users\\HP Probook\\Documents\\GitHub\\CV_task1_team15\\Images\\sudoku.png");

/* If image not found */
    // if (!image.data)                                                                          
    //     {  
    //     cout << "No image data \n";  
    //     return -1;  
    //     } 

//------------------------------------------------------------------------------------------
    // float data[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    // Create_Kernel(3, data);
    // imshow("Display", image);

    // Mat_<double> image2;
    // image2.size() = image.size();

    // int cols = image.cols, rows = image.rows;
    // cols = cols * rows;
    // rows = 1;

    // const uchar* image_ptr = image.ptr<uchar>(rows);
    // uchar* image2_ptr = image2.ptr<uchar>(rows);
    // for (int col = 0; col < cols; col++)
    // {

    //     image2_ptr[col] = (uchar) (0.2989 * image_ptr[0] + 0.5870 * image_ptr[1] + 0.1140 * image_ptr[2]) ;
    //     image_ptr +=3;

    // }
    // Mat image4;
    // image4.create(image.cols+2, image.rows+2, 0);
    // image4 = image.clone();
    // cout << image.size() << endl;
    // cout << (int) image4.at<uchar>(2,2) << endl;

    // hconcat(image, image4, image4);
    // imshow("Display", image4);
    // waitKey(0);

/* Convert Img To Gray Scale ------------------------------------------------------------------------ */

    Convert_To_Gray(src1, image);
    Convert_To_Gray(src2, image2);
    
    // Mat padded_img = Padd_Mono(image2,5);   

    // Mat sobel_x = Detect_Edges_Sobel_X(image2);

    // Mat robert = Robert_Edge(image2);


    // imshow("Display", image2);
    // waitKey(0);

// Add Noise To the Img --------------------------------------------------------------------
    // Add_Salt_And_Pepper_Noise(image2, image2, (float)0.05);


    // Add_Uniform_Noise(image2, image3, 250, 0.5);
    // namedWindow("Anwar", WINDOW_AUTOSIZE);

    // Add_Gaussian_Noise(image2, image3, 125, 25, 0.2);

// Apply Filters To Noised Img -------------------------------------------------------------
    // Add_Median_Filter(image2, image3);

    // Add_Average_Filter(image2,AvgFilterImg);

    // gaussian_Filter(image2, GaussianFilterImg);

    // Mat filtered = Gaussian_Filter(image2);

    // GaussianBlur(image2, image3, Size(5, 5), 0);

// Apply Low and High pass filters in frequency domain -------------------------------------

//    Add_Low_High_Frequency_Filter(image2, InversImg);
//     namedWindow("Original", WINDOW_AUTOSIZE);
//     imshow("Original", image2);

//     namedWindow("Fourier", WINDOW_AUTOSIZE);
//     imshow("Fourier", InversImg);
    
// Apply Hybrid Images -----------------------------------------------------------------------

   Apply_Hybrid_Images(image ,image2 , Hybrid_low ,Hybrid_High);
    namedWindow("Hybrid_low", WINDOW_AUTOSIZE);
    imshow("Hybrid_low", Hybrid_low);
    namedWindow("Hybrid_High", WINDOW_AUTOSIZE);
    imshow("Hybrid_High", Hybrid_High);

//Showing Median Filter Img ------------------------------------------------------------------    
    // hconcat(image2, image3, image3);
    // namedWindow("Median-Filter", WINDOW_AUTOSIZE);
    // imshow("Median-Filter", image3);

//Showing Average Filter Img ------------------------------------------------------------------
    // hconcat(image2, AvgFilterImg, AvgFilterImg);
    // namedWindow("Average-Filter", WINDOW_AUTOSIZE);
    // imshow("Average-Filter", AvgFilterImg);

//Showing gaussian Filter Img ------------------------------------------------------------------

    // namedWindow("Original", WINDOW_AUTOSIZE);
    // imshow("Original", image2);
    // hconcat(image3, filtered, filtered);
    // namedWindow("Gaussian_Noise", WINDOW_AUTOSIZE);
    // imshow("Gaussian_Noise", image3);

    // namedWindow("Gaussian_Filter_Implmented", WINDOW_AUTOSIZE);
    // imshow("Gaussian_Filter_Implmented", filtered);


    // namedWindow("sobel_x", WINDOW_AUTOSIZE);
    // imshow("sobel_x", sobel_x);

    // namedWindow("robert", WINDOW_AUTOSIZE);
    // imshow("robert", robert);

//Showing low and high pass filters ------------------------------------------------------------

    // namedWindow("Original", WINDOW_AUTOSIZE);
    // imshow("Original", image2);

    // namedWindow("Inverse_Fourier", WINDOW_AUTOSIZE);
    // imshow("Inverse_Fourier", InversImg);
    
   
    waitKey(0);
}

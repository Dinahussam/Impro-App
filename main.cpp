#include "Noise/noise.hpp"
#include "Noise/remove_noise.hpp"

#include "Filters/sobel.hpp"
#include "Filters/gaussian.hpp"
#include "Filters/prewitt.hpp"
#include "Filters/robert.hpp"

#include "Frequency/frequency.hpp"


// Mat magnitude(const Mat &src)
// {
//     // Mat mag = Mat::zeros(Size(sobel_x.cols, sobel_x.rows), CV_64FC1);
//     Mat mag = Mat::zeros(Size(src.cols, src.rows), CV_8UC1);

//     for (int i = 0; i < src.rows; i++)
//     {
//         for (int j = 0; j < src.cols; j++)
//         {
//             mag.at<uchar>(i, j) = sqrt(pow(src.at<Vec2b>(i, j)[0], 2) + pow(src.at<Vec2b>(i, j)[1], 2));

//         }
//     }
//     // print sobel
//     cout << mag << endl;
//     return mag;
// }


int main()
{

    Mat image;
    Mat image2;
    Mat image3;
    Mat AvgFilterImg;
    Mat GaussianFilterImg;
// --------------------------------------- Img Read ---------------------------------------
    image = imread("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Images\\sudoku.png");
        // image = imread("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Images\\lenna.png");


/* If image not found */
    if (!image.data)                                                                          
        {  
        cout << "No image data \n";  
        return -1;  
        } 

        // cout << "Wlecomeeeeeeeeeeeeeeeeeeeee" <<endl;
        // float x = 255;
        // cout << x << endl;

/* Convert Img To Gray Scale */
    Convert_To_Gray(image, image2);
    cout << "Type: " << image2.type() << endl;
    cout << "Channels: " << image2.channels() << endl;

    Mat fImage;
    image2.convertTo(fImage, CV_32F);

    Mat fourierTransform;
    dft(fImage, fourierTransform, DFT_SCALE|DFT_COMPLEX_OUTPUT);

    cout << "***********************************************************************" << endl ;
    cout << "Type: " << fourierTransform.type() << endl;
    cout << "Channels: " << fourierTransform.channels() << endl;

    // print one channel of fourierTransform
    cout << fourierTransform.at<Vec2f>(0, 0)[0] << endl;

    cout << fourierTransform.at<Vec2f>(0, 0)[1] << endl;
    


    // cout << "***********************************************************************" << endl ;
    // cout << "Type: " << fourier_show.type() << endl;
    // cout << "Channels: " << fourier_show.channels() << endl;

    // dft(fImage, fourierTransform,  );
    // fourierTransform = abs(fourierTransform);
    // Mat fourier_show = magnitude(fourierTransform);

    // // Mat fourier_show =  (uchar)sqrt(pow(sobel_x.at<Vec3b>(i, j)[c], 2) + pow(sobel_y.at<Vec3b>(i, j)[c], 2));
    // // Mat fourier_show;
    // // fourierTransform.convertTo(fourier_show, CV_8U);

    // // Print type and channels
    // cout << "***********************************************************************" << endl ;
    // cout << "Type: " << fourier_show.type() << endl;
    // cout << "Channels: " << fourier_show.channels() << endl;

    // Mat inverseTransform;
    // dft(fourierTransform, inverseTransform, DFT_INVERSE|DFT_REAL_OUTPUT);

    // Mat inverse_show;
    // inverseTransform.convertTo(inverse_show, CV_8U);

    // // Print type and channels
    // cout << "***********************************************************************" << endl ;
    // cout << "Type: " << inverse_show.type() << endl;
    // cout << "Channels: " << inverse_show.channels() << endl;

/* Plotting*/
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);

    // namedWindow("Fourier", WINDOW_AUTOSIZE);
    // imshow("Fourier", fourierTransform);

    // namedWindow("Inverse_Fourier", WINDOW_AUTOSIZE);
    // imshow("Inverse_Fourier", inverse_show);


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

    // Mat padded = Padd_Mono(image2,5);
    // padded.convertTo(padded, CV_8U);

    // Mat sobel_x = Mat::zeros(Size(image2.cols, image2.rows), image2.type());

    // Mat sobel_x = Detect_Edges_Sobel_X(image2);
    // // sobel_x.convertTo(sobel_x, CV_8U);

    // Mat sobel_y = Detect_Edges_Sobel_Y(image2);
    // sobel_y.convertTo(sobel_y, CV_8U);

    // Mat sobel = Detect_Edges_Sobel(image2);
    
    // Mat sobel_mag = Detect_Edges_Sobel_Magnitude_Gradient(image2);

    // // Mat sobel_new_mag = sqrt(pow(sobel_x, 2) + pow(sobel_y.at<float>(i, j), 2));

    // Mat sobel_phase = Detect_Edges_Sobel_Phase_Gradient(image2);
    // // sobel_phase.convertTo(sobel_phase, CV_8U);

    // Mat filtered = Gaussian_Filter(image2);
    // Mat new_filtered = Gaussian_Filter_new(image2);

    // GaussianBlur(image2, image3, Size(5, 5), 0);


//Plotting ------------------------------------------------------------------


    // namedWindow("padded", WINDOW_AUTOSIZE);
    // imshow("padded", padded);

    // namedWindow("Gaussian_Built_in", WINDOW_AUTOSIZE);
    // imshow("Gaussian_Built_in", image3);

    // namedWindow("Gaussian_Filter_Implmented", WINDOW_AUTOSIZE);
    // imshow("Gaussian_Filter_Implmented", filtered);

    // namedWindow("new_filtered", WINDOW_AUTOSIZE);
    // imshow("new_filtered", new_filtered);

    // namedWindow("sobel_x", WINDOW_AUTOSIZE);
    // imshow("sobel_x", sobel_x);
    // // imwrite("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Saved_Images\\sobel_x.png", sobel_x);

    // namedWindow("sobel_y", WINDOW_AUTOSIZE);
    // imshow("sobel_y", sobel_y);

    // namedWindow("sobel", WINDOW_AUTOSIZE);
    // imshow("sobel", sobel);

    // namedWindow("sobel_mag", WINDOW_AUTOSIZE);
    // imshow("sobel_mag", sobel_mag);

    // namedWindow("sobel_phase", WINDOW_AUTOSIZE);
    // imshow("sobel_phase", sobel_phase);

    // namedWindow("robert", WINDOW_AUTOSIZE);
    // imshow("robert", robert);
    
    waitKey(0);
}

#include "Noise/noise.cpp"
// #include "Noise/remove_noise.cpp"
// #include "Filters/convolution.cpp"

#include "Filters/sobel.cpp"

// #include "Noise/gaussian.cpp"
// #include "Filters/convolution.cpp"
// #include "Filters/sobel.cpp
// #include "Filters/prewitt.cpp"

Mat Gaussian_Filter(const Mat &src)
{

    // float gaussian_data[9] = {1,2,1,2,4,2,1,2,1};
    float gaussian_data[25] = {1,4,7,4,1,4,16,26,16,4,7, 26, 41, 26, 7,4,16,26,16,4, 1,4,7,4,1};
    Mat gaussian_kernel = Mat(5, 5, CV_32F, gaussian_data);
    if (src.type() == 16)
    {
        Mat convoluted = Convolute_2d_RGB(src, gaussian_kernel);
        return convoluted;
    }
    else if (src.type() == 0)
    {
        Mat convoluted = Convolute_2d_Mono(src, gaussian_kernel,GAUSSIAN_FILTER_5,2);
        return convoluted;
    }
    else
    {
        cout << "Error: Image type not supported" << endl;
        return src;
    }
}

Mat Robert_Edge(const Mat &src)
{

    // float robert_data[4] = {1,0,0,-1};
    float robert_data[9] = {0,0,0,0,1,0,0,0,-1};
    Mat robert_kernel = Mat(3, 3, CV_32F, robert_data);
    if (src.type() == 16)
    {
        Mat convoluted = Convolute_2d_RGB(src, robert_kernel);
        return convoluted;
    }
    else if (src.type() == 0)
    {
        Mat convoluted = Convolute_2d_Mono(src, robert_kernel,1,2);
        return convoluted;
    }
    else
    {
        cout << "Error: Image type not supported" << endl;
        return src;
    }
}






int main()
{

    Mat image;
    Mat image2;
    Mat image3;
    Mat AvgFilterImg;
    Mat GaussianFilterImg;
// --------------------------------------- Img Read ---------------------------------------
    image = imread("I:\\SBME 6th Term\\Computer Vision\\Projects & Tasks\\Project 1\\CV_task1_team15\\sudoku.png");

/* If image not found */
    if (!image.data)                                                                          
        {  
        cout << "No image data \n";  
        return -1;  
        } 

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

/* Convert Img To Gray Scale */
    Convert_To_Gray(image, image2);
    // Mat padded_img = Padd_Mono(image2,5);
    

    Mat sobel_x = Detect_Edges_Sobel_X(image2);

    Mat robert = Robert_Edge(image2);


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

    Mat filtered = Gaussian_Filter(image2);

    GaussianBlur(image2, image3, Size(5, 5), 0);

//Showing Median Filter Img ------------------------------------------------------------------    
    // hconcat(image2, image3, image3);
    // namedWindow("Median-Filter", WINDOW_AUTOSIZE);
    // imshow("Median-Filter", image3);

//Showing Average Filter Img ------------------------------------------------------------------
    // hconcat(image2, AvgFilterImg, AvgFilterImg);
    // namedWindow("Average-Filter", WINDOW_AUTOSIZE);
    // imshow("Average-Filter", AvgFilterImg);

//Showing gaussian Filter Img ------------------------------------------------------------------

    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image2);
    // hconcat(image3, filtered, filtered);
    namedWindow("Gaussian_Noise", WINDOW_AUTOSIZE);
    imshow("Gaussian_Noise", image3);

    namedWindow("Gaussian_Filter_Implmented", WINDOW_AUTOSIZE);
    imshow("Gaussian_Filter_Implmented", filtered);

    
    namedWindow("sobel_x", WINDOW_AUTOSIZE);
    imshow("sobel_x", sobel_x);
    namedWindow("robert", WINDOW_AUTOSIZE);
    imshow("robert", robert);
    
    waitKey(0);
}

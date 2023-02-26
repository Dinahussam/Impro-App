#include "Noise/noise.cpp"
#include "Noise/remove_noise.cpp"
#include "Filters/convolution.cpp"
// #include "Filters/sobel.cpp
// #include "Filters/prewitt.cpp"


int main()
{

    Mat image;
    Mat image2;
    Mat image3;
    Mat AvgFilterImg;
// --------------------------------------- Img Read ---------------------------------------
    image = imread("C:\\Users\\HP Probook\\Documents\\GitHub\\CV_task1_team15\\lenna.png");

/* If image not found */
    if (!image.data)                                                                          
        {  
        cout << "No image data \n";  
        return -1;  
        } 

//------------------------------------------------------------------------------------------


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


    // imshow("Display", image2);
    // waitKey(0);

// Add Noise To the Img --------------------------------------------------------------------
    Add_Salt_And_Pepper_Noise(image2, image2, (float)0.05);


    // Add_Uniform_Noise(image2, image3, 250, 0.5);
    // namedWindow("Anwar", WINDOW_AUTOSIZE);

    // Add_Gaussian_Noise(image2, image3, 125, 25, 1);


// Apply Filters To Noised Img -------------------------------------------------------------
    Add_Median_Filter(image2, image3);

    Add_Average_Filter(image2,AvgFilterImg);

  
    
//Showing Median Filter Img ------------------------------------------------------------------    
    hconcat(image2, image3, image3);
    namedWindow("Median-Filter", WINDOW_AUTOSIZE);
    imshow("Median-Filter", image3);

//Showing Average Filter Img ------------------------------------------------------------------
    hconcat(image2, AvgFilterImg, AvgFilterImg);
    namedWindow("Average-Filter", WINDOW_AUTOSIZE);
    imshow("Average-Filter", AvgFilterImg);
    
    waitKey(0);
}

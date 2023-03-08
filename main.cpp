#include "Noise/noise.hpp"
#include "Noise/remove_noise.hpp"
#include "Filters/sobel.hpp"
#include "Filters/gaussian.hpp"
#include "Filters/prewitt.hpp"
#include "Filters/robert.hpp"
#include "Frequency/frequency.hpp"

#include "Filters/canny.hpp"
#include "Common.hpp"

int main()
{
    Mat image;
    Mat grey_img;
// --------------------------------------- Img Read ---------------------------------------
    // image = imread("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Images\\building.png");
    image = imread("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Images\\sudoku.png");
        // image = imread("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Images\\lenna.png");

/* If image not found */
    if (!image.data)                                                                          
        {  
        cout << "No image data \n";  
        return -1;  
        } 

/* Convert Img To Gray Scale */
    Convert_To_Gray(image, grey_img);

    cout << "***********************************************************************" << endl ;

    Mat Canny = Detect_Edges_Canny(grey_img);

    // // FIRST SMOOTH IMAGE
    // Mat blurred = Gaussian_Filter_new(grey_img);

    // // THEN calculate sobel magnitude and phase gradients
    // Mat magnitude_gradient = Detect_Edges_Sobel_Magnitude_Gradient(blurred);

    // Mat phase = Detect_Edges_Sobel_Phase_Gradient(blurred);

    // // print size of magnitude and phase
    // cout << "********************************************" <<endl;
    // cout << "size of magnitude is " << magnitude_gradient.size() << endl;
    // cout << "size of phase is " << phase.size() << endl;
    // // print types
    // cout << "type of magnitude is " << magnitude_gradient.type() << endl;
    // cout << "type of phase is " << phase.type() << endl;


    // // Sobel_Phase_Gradient.convertTo(Sobel_Phase_Gradient, CV_8UC1);

    // // THEN SUPRESS NON-MAXIMUM EDGES

    // // Mat Suppressed = Supression(Sobel_Magnitude_Gradient, Sobel_Phase_Gradient);

    // // cout << "value of pi is " << M_PI << endl;

    // cout <<"Phase = "<< phase.at<float>(0, 0) << endl;
    // cout << "type of Phase is " << phase.type() << endl;

    // Mat angles = phase * 180 / M_PI;
    // cout <<"Angles =" <<angles.at<float>(0, 0) << endl;

    // // print type of angles
    // cout << "type of angles is " << angles.type() << endl;
    // // print channels of angles
    // cout << "channels of angles is " << angles.channels() << endl;

    // Mat suppressed = Mat::zeros(Size(magnitude_gradient.cols, magnitude_gradient.rows), magnitude_gradient.type());
    // // print size of suppressed
    // cout << "size of suppressed is " << suppressed.size() << endl;
    // // print type of suppressed
    // cout << "type of suppressed is " << suppressed.type() << endl;

    // float neighbour_1 , neighbour_2;

    // for (int i = 1; i < angles.rows-1; i++)
    // {
    //     for (int j = 1; j < angles.cols-1; j++)
    //     {
    //         // angle 0
    //         if ( (angles.at<float>(i, j) < 22.5) || (angles.at<float>(i, j) >= 157.5 ) )
    //         {
    //             // cout << "hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" <<endl ;
    //             neighbour_1 = magnitude_gradient.at<uchar>(i, j+1);
    //             neighbour_2 = magnitude_gradient.at<uchar>(i, j-1);
    //         }
    //          // angle 45
    //         else if ( (angles.at<float>(i, j) >= 22.5) && (angles.at<float>(i, j) <= 67.5) )
    //         {
    //             neighbour_1 = magnitude_gradient.at<uchar>(i+1,j-1);
    //             neighbour_2 = magnitude_gradient.at<uchar>(i-1,j+1);           
    //         }
    //         // angle 90
    //         else if ( (angles.at<float>(i, j) >= 67.5) && (angles.at<float>(i, j) <112.5) )
    //         {
    //             neighbour_1 = magnitude_gradient.at<uchar>(i+1,j);
    //             neighbour_2 = magnitude_gradient.at<uchar>(i-1,j);
    //         }
    //         // angle 135
    //         else if ( (angles.at<float>(i, j) >= 112.5) && (angles.at<float>(i, j) < 157.5) )
    //         {
    //             neighbour_1 = magnitude_gradient.at<uchar>(i-1, j-1);
    //             neighbour_2 = magnitude_gradient.at<uchar>(i+1, j+1);
    //         }

    //         // check pixel with its neighbour pixels
    //         if ( (magnitude_gradient.at<uchar>(i, j) >= neighbour_1) && (magnitude_gradient.at<uchar>(i, j) >= neighbour_2))
    //         {
    //             suppressed.at<uchar>(i, j) = magnitude_gradient.at<uchar>(i, j);
    //         }
    //         else
    //         {
    //             suppressed.at<uchar>(i, j) = 0;
    //         }
            
    //     }
    // }

    // // THEN APPLY THRESHOLDING
    // Mat thresholded = Double_Threshoulding(suppressed);

    // // THEN APPLY HYSTERESIS
    // Mat hysteresis = Hysteresis(thresholded);


/*     //Initialize m
    double minVal; 
    double maxVal; 
    Point minLoc; 
    Point maxLoc;

    minMaxLoc( angles, &minVal, &maxVal, &minLoc, &maxLoc );

    cout << "min val: " << minVal << endl;
    cout << "max val: " << maxVal << endl;

    cout << "min val Location: " << minLoc << endl;
    cout << "max val Location: " << maxLoc << endl;

    // // print min value location x and y
    cout << "min val Location x: " << minLoc.x << endl;
    cout << "min val Location y: " << minLoc.y << endl;  */

    /******************************************* Plotting**************************************************/

    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", grey_img);

    namedWindow("Canny", WINDOW_AUTOSIZE);
    imshow("Canny", Canny);




    waitKey(0);
        
        return 0;
        }

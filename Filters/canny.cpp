#include "canny.hpp"

Mat Double_Threshoulding(Mat &suppressed, float lowThreshold/*  = 0.05 */, float highThreshold /* = 0.09 */)
{
    Mat thresholded = Mat::zeros(Size(suppressed.cols, suppressed.rows), suppressed.type());

    // find the maximum value of the suppressed image
    double maxVal;
    minMaxLoc(suppressed, NULL, &maxVal, NULL, NULL);

    // float highThreshold = highThresholdRatio * maxVal;
    // float lowThreshold = highThreshold * lowThresholdRatio;

    // lowThreshold = 30;
    // highThreshold = 80;

    for (int i = 0; i < suppressed.rows - 1; i++)
    {
        for (int j = 0; j < suppressed.cols - 1; j++)
        {
            if (suppressed.at<uchar>(i, j) > highThreshold)
            {
                thresholded.at<uchar>(i, j) = STRONG_EDGE;
            }
            else if ((suppressed.at<uchar>(i, j) < highThreshold) && (suppressed.at<uchar>(i, j) > lowThreshold))
            {
                thresholded.at<uchar>(i, j) = WEAK_EDGE ;
            }
            else
            {
                thresholded.at<uchar>(i, j) = 0;
            }
        }
    }
    return thresholded;
}

Mat Hysteresis (Mat &thresholded)
{
    Mat hysteresis = thresholded.clone();
    for (int i = 1; i < thresholded.rows - 1; i++)
    {
        for (int j = 1; j < thresholded.cols - 1; j++)
        {
            if (thresholded.at<uchar>(i, j) == WEAK_EDGE)
            {
                if ( (thresholded.at<uchar>(i+1, j-1) == STRONG_EDGE) || (thresholded.at<uchar>(i+1, j) == STRONG_EDGE) || (thresholded.at<uchar>(i+1, j+1) == STRONG_EDGE) || (thresholded.at<uchar>(i, j-1) == STRONG_EDGE) || (thresholded.at<uchar>(i, j+1) == STRONG_EDGE) || (thresholded.at<uchar>(i-1, j-1) == STRONG_EDGE) || (thresholded.at<uchar>(i-1, j) == STRONG_EDGE) || (thresholded.at<uchar>(i-1, j+1) == STRONG_EDGE) )
                {
                    hysteresis.at<uchar>(i, j) = STRONG_EDGE;
                }
                else
                {
                    hysteresis.at<uchar>(i, j) = 0;
                }
            }
        }
    }
    return hysteresis;
}

Mat Supression( Mat &magnitude_gradient,  Mat &phase_gradient)
{
    Mat suppressed = Mat::zeros(Size(magnitude_gradient.cols, magnitude_gradient.rows), magnitude_gradient.type());

    // convert phase from radian to angles
    Mat angles = phase_gradient * 180 / M_PI;

    float neighbour_1 , neighbour_2;

    for (int i = 1; i < angles.rows-1; i++)
    {
        for (int j = 1; j < angles.cols-1; j++)
        {
            // angle 0
            if ( (angles.at<float>(i, j) < 22.5) || (angles.at<float>(i, j) >= 157.5 ) )
            {
                // cout << "hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" <<endl ;
                neighbour_1 = magnitude_gradient.at<uchar>(i, j+1);
                neighbour_2 = magnitude_gradient.at<uchar>(i, j-1);
            }
             // angle 45
            else if ( (angles.at<float>(i, j) >= 22.5) && (angles.at<float>(i, j) <= 67.5) )
            {
                neighbour_1 = magnitude_gradient.at<uchar>(i+1,j-1);
                neighbour_2 = magnitude_gradient.at<uchar>(i-1,j+1);           
            }
            // angle 90
            else if ( (angles.at<float>(i, j) >= 67.5) && (angles.at<float>(i, j) <112.5) )
            {
                neighbour_1 = magnitude_gradient.at<uchar>(i+1,j);
                neighbour_2 = magnitude_gradient.at<uchar>(i-1,j);
            }
            // angle 135
            else if ( (angles.at<float>(i, j) >= 112.5) && (angles.at<float>(i, j) < 157.5) )
            {
                neighbour_1 = magnitude_gradient.at<uchar>(i-1, j-1);
                neighbour_2 = magnitude_gradient.at<uchar>(i+1, j+1);
            }

            // check pixel with its neighbour pixels
            if ( (magnitude_gradient.at<uchar>(i, j) >= neighbour_1) && (magnitude_gradient.at<uchar>(i, j) >= neighbour_2))
            {
                suppressed.at<uchar>(i, j) = magnitude_gradient.at<uchar>(i, j);
            }
            else
            {
                suppressed.at<uchar>(i, j) = 0;
            }
            
        }
    }
    return suppressed;
}


Mat Detect_Edges_Canny( const Mat &src,  float lowThresholdRatio /* = 0.05 */, float highThresholdRatio /* 0.09 */ ) 
{
    // FIRST SMOOTH IMAGE
    Mat blurred = Gaussian_Filter_new(src);
    cout << "****************************** After blur ****************************" << endl;

    // THEN calculate sobel magnitude and phase gradients
    Mat magnitude_gradient = Detect_Edges_Sobel_Magnitude_Gradient(blurred);

    Mat phase_gradient = Detect_Edges_Sobel_Phase_Gradient(blurred);

    // THEN SUPRESS NON-MAXIMUM EDGES
    Mat suppressed = Supression(magnitude_gradient, phase_gradient);

    // THEN APPLY THRESHOLDING
    Mat thresholded = Double_Threshoulding(suppressed,lowThresholdRatio,highThresholdRatio);

    // THEN APPLY HYSTERESIS
    Mat canny_edges = Hysteresis(thresholded);


    namedWindow("blurred", WINDOW_AUTOSIZE);
    imshow("blurred", blurred);

    namedWindow("Sobel_Magnitude_Gradient", WINDOW_AUTOSIZE);
    imshow("Sobel_Magnitude_Gradient", magnitude_gradient);

    namedWindow("Sobel_Phase_Gradient", WINDOW_AUTOSIZE);
    imshow("Sobel_Phase_Gradient", phase_gradient);

    namedWindow("suppressed", WINDOW_AUTOSIZE);
    imshow("suppressed", suppressed);

    namedWindow("thresholded", WINDOW_AUTOSIZE);
    imshow("thresholded", thresholded);

    namedWindow("hysteresis", WINDOW_AUTOSIZE);
    imshow("hysteresis", canny_edges);

    return canny_edges;
}
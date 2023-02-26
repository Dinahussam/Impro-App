#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;


Mat Detect_Edges_Prewitt_X(const Mat &src)
{

    float prewitt_x_data[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    Mat kernel_prewitt_x = Mat(3, 3, CV_32F, prewitt_x_data);
    if (src.type() == 16)
    {
        Mat prewitt_x_img = Convolute_2d_RGB(src, kernel_prewitt_x);
        return prewitt_x_img;
    }
    else if (src.type() == 0)
    {
        Mat prewitt_x_img = Convolute_2d_Mono(src, kernel_prewitt_x);
        return prewitt_x_img;
    }
    else
    {
        cout << "Error: Image type not supported" << endl;
        return src;
    }
}

Mat Detect_Edges_Prewitt_Y(const Mat &src)
{
    float prewitt_y_data[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    Mat kernel_prewitt_y = Mat(3, 3, CV_32F, prewitt_y_data);
    if (src.type() == 16)
    {
        Mat prewitt_y_img = Convolute_2d_RGB(src, kernel_prewitt_y);
        return prewitt_y_img;
    }
    else if (src.type() == 0)
    {
        Mat prewitt_y_img = Convolute_2d_Mono(src, kernel_prewitt_y);
        return prewitt_y_img;
    }
    else
    {
        cout << "Error: Image type not supported" << endl;
        return src;
    }
}

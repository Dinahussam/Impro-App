// #include <opencv2/opencv.hpp>
// #include <cmath>


// using namespace cv;
// using namespace std;



// Mat Gaussian_Filter(const Mat &src)
// {
//     float gaussian_data[9] = {1,2,1,2,4,2,1,2,1};
//     Mat kernel_sobel_y = Mat(3, 3, CV_32F, gaussian_data);
//     if (src.type() == 16)
//     {
//         Mat convoluted_y = Convolute_2d_RGB(src, kernel_sobel_y);
//         return convoluted_y;
//     }
//     else if (src.type() == 0)
//     {
//         Mat convoluted_y = Convolute_2d_Mono(src, kernel_sobel_y);
//         return convoluted_y;
//     }
//     else
//     {
//         cout << "Error: Image type not supported" << endl;
//         return src;
//     }
// }
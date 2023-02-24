#include "noise.cpp"

int main()
{

    Mat image;
    Mat image2;
    image = imread("D:\\College life\\Advanced projects\\CV_Task1\\lenna.png");

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

    Convert_To_Gray(image, image2);
    // imshow("Display", image2);
    // waitKey(0);
    Mat image3 = image2.clone();
    Add_Gaussian_Noise(image2, image3, 125, 25, 1);
    // Add_Uniform_Noise(image2, image3, 250, 0.5);
    // namedWindow("Anwar", WINDOW_AUTOSIZE);
    hconcat(image2, image3, image3);
    imshow("Display", image3);
    waitKey(0);
}

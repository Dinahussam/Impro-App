#include"helper_functions.hpp"


/*------------------------------- Helper Functions -----------------------------------*/

void Convert_To_Gray(const Mat &src, Mat &dst)
{
    int rows = src.rows, cols = src.cols;

    dst.create(src.size(), 0);

    cols = rows * cols;
    rows = 1;

    for (int row = 0; row < rows; row++)
    {
        const uchar* src_ptr = src.ptr<uchar>(row);
        uchar* dst_ptr = dst.ptr<uchar>(row);

        for (int col = 0; col < cols; col++)
        {
            dst_ptr[col] = (uchar)(src_ptr[0] * 0.114f + src_ptr[1] * 0.587f + src_ptr[2] * 0.299f);
            src_ptr += 3;
        }
    }
}


void Swap_Elements(unsigned char *first_element, unsigned char *second_element)
{
    unsigned char temp = *first_element;
    *first_element = *second_element;
    *second_element = temp;
}

void Bubble_Sort(unsigned char array[], unsigned char size)
{
    int first_index, second_index;
    for (first_index = 0; first_index < size - 1; first_index++)
        for (second_index = 0; second_index < size - first_index - 1; second_index++)
            if (array[second_index] > array[second_index + 1])
                Swap_Elements(&array[second_index], &array[second_index + 1]);
}

Mat Create_Kernel(int kernel_size, unsigned char *kernel_data, int image_type)
{
    Mat kernel = Mat::zeros(Size(kernel_size, kernel_size), image_type);
    int data_index = 0;
    cout << "-------------" << endl;
    for (int row = 0; row < kernel_size; row++)
    {
        for (int col = 0; col < kernel_size; col++)
        {
            kernel.at<uchar>(row, col) = kernel_data[data_index];
            data_index++;
        }
    }
    cout << data_index << endl;
    return kernel;
}


/*****************************************************************************************************************************************/

Mat Padd_Mono(const Mat &src, int padding_margin , int data_type)
{
    Mat padding_img;
    if (data_type == UCHAR_FLAG)
    {
        padding_img =  Mat::zeros(Size(src.cols + padding_margin * 2, src.rows + padding_margin * 2), src.type());
    }
    else if (data_type == FLOAT_FLAG)
    {
        padding_img =  Mat::zeros(Size(src.cols + padding_margin * 2, src.rows + padding_margin * 2), CV_32FC1);
    }

    // Mat padding_img = Mat::zeros(Size(src.cols + padding_margin * 2, src.rows + padding_margin * 2), src.type());
    // Padding ----------------------------------------------------
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if (data_type == UCHAR_FLAG)
            {
                padding_img.at<uchar>(i + padding_margin, j + padding_margin) = src.at<uchar>(i, j);
            }
            else if (data_type == FLOAT_FLAG)
            {
                padding_img.at<float>(i + padding_margin, j + padding_margin) = src.at<float>(i, j);
            }
        }
    }
    return padding_img;
}

/*****************************************************************************************************************************************/

Mat Padd_RGB(const Mat &src, int padding_margin)
{
    Mat padding_img = Mat::zeros(Size(src.cols + padding_margin * 2, src.rows + padding_margin * 2), src.type());

    // Padding ----------------------------------------------------
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            // copy rgb to rgb
            for (int c = 0; c < 3; c++)
            {
                padding_img.at<Vec3b>(i + padding_margin, j + padding_margin)[c] = src.at<Vec3b>(i, j)[c];
            }
        }
    }
    return padding_img;
}

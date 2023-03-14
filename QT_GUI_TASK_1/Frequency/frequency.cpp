#include "frequency.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"





/* --------------------------- filter construction ------------------------------*/

Mat Filter_Construction( Mat &scr, float Radius , float filter_flag)

{
    // construction filter with same image size and with (1) values
    Mat filter(scr.size(), CV_32F, Scalar(1- filter_flag));

    // initialize the distance between the center and any point 
	float Distance = 0;

		for (int x = 0; x < filter.rows; x++)
		{
			for (int  y = 0; y < filter.cols; y++)
			{
				Distance = sqrt((x - scr.rows / 2)*(x - scr.rows / 2) + (y - scr.cols / 2)*(y - scr.cols / 2));

				if (Distance > Radius)
				{
                    filter.at<float>(x, y) = filter_flag;
				}
			}
		}
		return filter;
}

/* --------------------------- fourier output shifting ------------------------------*/

Mat fourier_shifting( Mat &fourier_input_img)
{
	Mat fourier_output_img = fourier_input_img.clone();
	int cx = fourier_output_img.cols / 2;
	int cy = fourier_output_img.rows / 2;

    // divide the fourier input img into four parts ----------------------------------
    // rect ( x, y , w, h)
	Mat left_up(fourier_output_img, Rect(0, 0, cx, cy));
	Mat right_up(fourier_output_img, Rect(cx, 0, cx, cy));
	Mat left_down(fourier_output_img, Rect(0, cy, cx, cy));
	Mat right_down(fourier_output_img, Rect(cx, cy, cx, cy));

    // switch the four parts places to center the fourier transform ------------------
	Mat switch_variable;
	left_up.copyTo(switch_variable);
	right_down.copyTo(left_up);
	switch_variable.copyTo(right_down);
	right_up.copyTo(switch_variable);
	left_down.copyTo(right_up);
	switch_variable.copyTo(left_down);

    return fourier_output_img;
}

/* --------------------------- Calculate the fourier Transform ------------------------------*/

Mat Apply_Fourier_Transform( Mat &src)
{
	Mat fourierImage;
    dft(src, fourierImage, DFT_SCALE|DFT_COMPLEX_OUTPUT);

    return fourierImage;
}
	
/* --------------------------------- Applying Filtering ---------------------------------------*/

Mat Apply_Filtering( Mat &fourierImgInput , float filterRadius, float flag)
{

	Mat real, imaginary;
	Mat planes[] = { real, imaginary };
	split(fourierImgInput, planes);
	
    Mat real_shifted = fourier_shifting(planes[0]);
    Mat imaginary_shifted = fourier_shifting(planes[1]);

    Mat constructionFilter = Filter_Construction(fourierImgInput, filterRadius, flag);

    Mat planes_out[] = { Mat::zeros(fourierImgInput.size(), CV_32F), Mat::zeros(fourierImgInput.size(), CV_32F) };
    planes_out[0] = constructionFilter.mul(real_shifted);
    planes_out[1] = constructionFilter.mul(imaginary_shifted);
    
    Mat real_shifted_img = fourier_shifting(planes_out[0]);
    Mat imaginary_shifted_img = fourier_shifting(planes_out[1]);
    Mat shifted_DFT_plane_img[] = {real_shifted_img ,imaginary_shifted_img };

	Mat MergeImg;
	merge(shifted_DFT_plane_img, 2, MergeImg);

	return MergeImg;
    
}
	

/* --------------------------- Calculate the inverse fourier Transform ------------------------------*/

  Mat Inverse_Fourier_Transform( Mat &src)
  {
    Mat inverseImage;
	src.copyTo(inverseImage);
    dft(inverseImage, inverseImage, DFT_INVERSE|DFT_REAL_OUTPUT);

	return inverseImage;
  } 


/*-------------------------------- Frequency Domain  Filters ---------------------------*/


Mat Add_Low_High_Frequency_Filter( Mat &src, float filterRadius , float flag)
{ 
    Mat dst;
    src.copyTo(dst);
    dst.convertTo(dst, CV_32F);

    Mat fourierImage = Apply_Fourier_Transform(dst);
    Mat FilteringImg = Apply_Filtering(fourierImage, filterRadius , flag);
    Mat OutputImage = Inverse_Fourier_Transform(FilteringImg);

	OutputImage.convertTo(OutputImage, CV_8U);

	return OutputImage;
}


/*-------------------------------------------Hybrid Images -------------------------------------*/

Mat Apply_Hybrid_Images( Mat &src1 ,Mat &src2, bool H_L_Flag)
{
    Mat dst1;
    Mat dst2;
	src1.copyTo(dst1);
	src2.copyTo(dst2);


// resize images to start making hybrid 
    int down_width = 512;
    int down_height = 512;
	Mat resized_down_img1;
	Mat resized_down_img2;
    resize(dst1, resized_down_img1, Size(down_width, down_height), INTER_LINEAR);
    resize(dst2, resized_down_img2, Size(down_width, down_height), INTER_LINEAR);

// Apply Low and High pass filters to both images 
    Mat Low_Frequency_Image = Add_Low_High_Frequency_Filter(resized_down_img1 , 30, H_L_Flag);
    Mat High_Frequency_Image = Add_Low_High_Frequency_Filter(resized_down_img2, 30 , !H_L_Flag);

	Mat Hybrid = Low_Frequency_Image+High_Frequency_Image;
	

    Low_Frequency_Image.copyTo(dst1);
	High_Frequency_Image.copyTo(dst2);

	return Hybrid ;
}





/*-------------------------------------------Report Addtional Function--------------------------*/

    
// switch to a logarithmic scale -----------------------------------------------------
	// mag_image += Scalar::all(1);
	// log(mag_image, mag_image);
	// mag_image = mag_image(Rect(0, 0, mag_image.cols & -2, mag_image.rows & -2));

	// normalize(shifted_DFT, shifted_DFT, 0, 1, NORM_MINMAX);

// Get the Magnitude of the image ----------------------------------------------------
    //Mat mag_image;
	//magnitude(planes[0], planes[1], mag_image);



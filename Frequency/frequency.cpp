#include "frequency.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"





/* --------------------------- filter construction ------------------------------*/

Mat Filter_Construction( Mat &scr, float Radius , float filter_flag)

{
    // construction filter with same image size and with (1) values
	Mat filter(scr.size(), CV_32F, Scalar(filter_flag));

    // cout << filter << endl;

    // initialize the distance between the center and any point 
	float Distance = 0;

		for (int x = 0; x < filter.rows; x++)
		{
			for (int  y = 0; y < filter.cols; y++)
			{
				Distance = sqrt((x - scr.rows / 2)*(x - scr.rows / 2) + (y - scr.cols / 2)*(y - scr.cols / 2));

				if (Distance > Radius)
				{
					filter.at<float>(x, y) = 1-filter_flag;
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

void Apply_Fourier_Transform(const Mat &src, Mat &dst ,float flag)
{
	src.copyTo(dst);

	Mat fourierImage;
	dft(dst, fourierImage, DFT_SCALE|DFT_COMPLEX_OUTPUT);

	Mat real, imaginary;
	Mat planes[] = { real, imaginary };
	split(fourierImage, planes);
	
    Mat real_shifted = fourier_shifting(planes[0]);
    Mat imaginary_shifted = fourier_shifting(planes[1]);
    Mat shifted_DFT_plane[] = {real_shifted , imaginary_shifted };
	
/* --------------------------------- Applying Filtering ---------------------------------------*/


	Mat copy1;
    Mat copy2;
    Mat constructionFilter = Filter_Construction(dst,10, flag);
    constructionFilter.copyTo(copy1);
    constructionFilter.copyTo(copy2);

    Mat planes_construction_filter[] = { copy1, copy2 };
    Mat planes_out[] = { Mat::zeros(dst.size(), CV_32F), Mat::zeros(dst.size(), CV_32F) };
    planes_out[0] = planes_construction_filter[0].mul(shifted_DFT_plane[0]);
	planes_out[1] = planes_construction_filter[1].mul(shifted_DFT_plane[1]);
    

    Mat real_shifted_img = fourier_shifting(planes_out[0]);
    Mat imaginary_shifted_img = fourier_shifting(planes_out[1]);
    Mat shifted_DFT_plane_img[] = {real_shifted_img ,imaginary_shifted_img };

/* --------------------------- Calculate the inverse fourier Transform ------------------------------*/
   
    Mat inverseImage;
    Mat MergeImg;
	merge(shifted_DFT_plane_img, 2, MergeImg);
    dft(MergeImg, inverseImage, DFT_INVERSE|DFT_REAL_OUTPUT);

    Mat OutputImage;    
    inverseImage.convertTo(OutputImage, CV_8U);
    OutputImage.copyTo(dst);

}




/*-------------------------------- Frequency Domain  Filters ---------------------------*/


void Add_Low_High_Frequency_Filter(const Mat &src, Mat &dst , float flag)
{
    src.copyTo(dst);

    Mat fLoat_Image;
    dst.convertTo(fLoat_Image, CV_32F);

    Mat fourierImage;
	Apply_Fourier_Transform(fLoat_Image,fourierImage,flag);

	fourierImage.copyTo(dst);
}





/*-------------------------------------------Hybrid Images -------------------------------------*/

void Apply_Hybrid_Images(const Mat &src1 ,Mat &src2 , Mat &dst1 , Mat &dst2)
{
	src1.copyTo(dst1);
	src2.copyTo(dst2);

	Mat Low_Frequency_Image;
	Mat High_Frequency_Image;

	Add_Low_High_Frequency_Filter(dst1 ,Low_Frequency_Image,1);
	Add_Low_High_Frequency_Filter(dst2 ,High_Frequency_Image,0);



    Low_Frequency_Image.copyTo(dst1);
	High_Frequency_Image.copyTo(dst2);
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



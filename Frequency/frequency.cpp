#include "frequency.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

/* --------------------------- filter construction ------------------------------*/

Mat Filter_Construction( Mat &scr, float Radius)
{
    // construction filter with same image size and with (1) values
	Mat filter(scr.size(), CV_32F, Scalar(1));

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
					filter.at<float>(x, y) = 0;
				}
			}
		}
		return filter;
}

/* --------------------------- fourier output shifting ------------------------------*/

void fourier_shifting(const Mat &fourier_input_img, Mat &fourier_output_img)
{
	fourier_output_img = fourier_input_img.clone();
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
}

/* --------------------------- Calculate the fourier Transform ------------------------------*/

void calculateDFT(Mat &scr, Mat &dst)
{
	// define mat consists of two mat, one for real values and the other for complex values
	Mat planes[] = { scr, Mat::zeros(scr.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);
    // cout<<"output----------------------------"<<endl;
    // cout<<complexImg<<endl;
	dft(complexImg, complexImg);
	complexImg.copyTo(dst);
}


/* --------------------------- Applying Filtering ------------------------------*/

void filtering(Mat &scr, Mat &dst, Mat &constructionFilter)
{
	// fourier_shifting(constructionFilter, constructionFilter);
	Mat planesH[] = { Mat_<float>(constructionFilter.clone()), Mat_<float>(constructionFilter.clone()) };

	Mat planes_dft[] = { scr, Mat::zeros(scr.size(), CV_32F) };
	split(scr, planes_dft);

	Mat planes_out[] = { Mat::zeros(scr.size(), CV_32F), Mat::zeros(scr.size(), CV_32F) };
	planes_out[0] = planesH[0].mul(planes_dft[0]);
	planes_out[1] = planesH[1].mul(planes_dft[1]);

	merge(planes_out, 2, dst);

}


Mat Masking ( Mat &src, Mat &mask)
{
	// Mat masked;
	Mat masked = Mat::zeros(Size(src.cols,src.rows),src.type());
	for (int x = 0; x < src.rows; x++)
		{
			for (int  y = 0; y < src.cols; y++)
			{
				masked.at<float>(x, y) = src.at<float>(x, y) * mask.at<float>(x, y);
			}
		}	return masked;
}


/*-------------------------------- Frequency Domain Low Pass Filter ---------------------------*/


void Add_Low_Frequency_Filter( Mat &src, Mat &dst)
{
    src.copyTo(dst);

    // cout << "************** Img before convertion for data type***************" << endl ;
    // cout << dst << endl;

    Mat fLoat_Image;
    dst.convertTo(fLoat_Image, CV_32F);

    // cout << "************** Img after convertion for data type***************" << endl ;
    // cout << fLoat_Image << endl;

    // expand input image to optimal size
	// Mat padded;
	// int m = getOptimalDFTSize(fLoat_Image.rows);
	// int n = getOptimalDFTSize(fLoat_Image.cols);
	// copyMakeBorder(fLoat_Image, padded, 0, m - fLoat_Image.rows, 0, n - fLoat_Image.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat fourierImage;
	dft(fLoat_Image, fourierImage, DFT_SCALE|DFT_COMPLEX_OUTPUT);
	// dft(fImage, fourierTransform, DFT_SCALE|DFT_COMPLEX_OUTPUT);

    Mat real, imaginary;
	Mat planes[] = { real, imaginary };

	split(fourierImage, planes);

	// shift each plane
	// fourier_shifting(fourierImage, fourierImage);

	// make mask to each splitted part
	Mat mask = Filter_Construction(src,5);

    Mat masked_real = Masking(planes[0],mask);
	Mat masked_imaginary = Masking(planes[1],mask);

	Mat masked_foureir;
	Mat masked_planes[] = { masked_real, masked_imaginary };


	merge(masked_planes, 2, masked_foureir);


	// merge(masked_real,masked_imaginary,masked_foureir);


	// Mat mag_image;
	// magnitude(planes[0], planes[1], mag_image);


	// calculate inverse fourier
	Mat inverseFourier;
	dft(masked_foureir, inverseFourier, DFT_INVERSE | DFT_REAL_OUTPUT);

	Mat inverse_show;
    inverseFourier.convertTo(inverse_show, CV_8U);

	// plot inverse fourier
	namedWindow("inverseFourier", WINDOW_AUTOSIZE);
    imshow("inverseFourier", inverse_show);



	// switch to a logarithmic scale
	// mag_image += Scalar::all(1);
	// log(mag_image, mag_image);
	// mag_image = mag_image(Rect(0, 0, mag_image.cols & -2, mag_image.rows & -2));

	// Mat shifted_DFT;
	// fourier_shifting(mag_image, shifted_DFT);

	// normalize(shifted_DFT, shifted_DFT, 0, 1, NORM_MINMAX);

	// namedWindow("Fourier", WINDOW_AUTOSIZE);
    // imshow("Fourier", shifted_DFT);

    // shifted_DFT.copyTo(dst);

    // cout << "************** Img after fourier***************" << endl ;
    // cout << fourierImage << endl;

	// Mat filter_construction = Filter_Construction(fourierImage ,5);

    // filtering
	// Mat complexIH;
	// filtering(fourierImage, complexIH, filter_construction);


    // Mat inverseImage;
    // dft(fourierImage, inverseImage, DFT_INVERSE|DFT_REAL_OUTPUT);

    // cout << "************** Img after inverse fourier***************" << endl ;
    // cout << inverseImage << endl;

    // normalize(inverseImage, inverseImage, 0, 1, NORM_MINMAX);

    // Mat OutputImage;
    // inverseImage.convertTo(OutputImage, CV_8U);

    // dst.copyTo(OutputImage);

    // Print type and channels
    // cout << "*************************" << endl ;
    // cout << "Type: " << OutputImage.type() << endl;
    // cout << "Channels: " << OutputImage.channels() << endl;
    
}





/*-------------------------------------------Hybrid Images -------------------------------------*/





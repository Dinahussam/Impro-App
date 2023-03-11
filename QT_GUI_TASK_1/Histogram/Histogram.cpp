#include "Histogram.hpp"

void calculate_histogram (Mat img_grayscale, map<int, int>& histo, vector<double>& cumulative_histo){
    for (int row = 0; row  < img_grayscale.rows; ++row ) {
        for (int col = 0; col < img_grayscale.cols; ++col) {
            int search = (int)img_grayscale.at<uchar>(row,col);
            if( histo.find(search) !=histo.end()){
                histo[search]++;
            }
            else{
                histo.insert({search, 1});
            }
        }
    }

    int accumalator = 0;
    for (auto itr = histo.begin(); itr != histo.end(); itr++){
                accumalator += int(itr->second);
                cumulative_histo.push_back(accumalator);
         }
}

Mat normalize_image(Mat &image){

        float image_min = image.at<uchar>(0 ,0), image_max = 0;
        for (int row = 0; row < image.rows; ++row) {
            for (int col = 0; col < image.cols; ++col) {
                if (image.at<uchar>(row ,col) <= image_min) {
                    image_min = image.at<uchar>(row ,col);
                }
                if (image.at<uchar>(row ,col) >= image_max) {
                    image_max = image.at<uchar>(row ,col);
                }
            }
        }
        for (int row = 0; row < image.rows; ++row) {
            for (int col = 0; col < image.cols; ++col) {
                image.at<uchar>(row, col) = ((float)(image.at<uchar>(row, col) - image_min)/(image_max - image_min))*255;
            }
        }
    return image;
}

vector<int> normalize_vector(vector <int> data){
    float data_min = data[0];
    float data_max = 0;
    for (int loop = 0; loop < (int)data.size(); ++loop) {
        if (data[loop] <= data_min) {
            data_min = data[loop];
        }
        if (data[loop] >= data_max) {
            data_max = data[loop];
        }
    }
    for (int loop = 0; loop < (int)data.size(); ++loop) {
        data[loop] = ((float)(data[loop]- data_min)/ (data_max - data_min))*255;
    }
    return data;
}

Mat Equalize_img(Mat &image){

    map<int, int> histo;
    vector<double> cumulative_histo;
    map<int, int> new_level;
    Mat output_image = image.clone();

    calculate_histogram(image, histo, cumulative_histo);
    float CDF = 0;
    int pixels_sum = 0;

    for (auto itr = histo.begin(); itr != histo.end(); itr++){
            pixels_sum += (itr->second);
         }
    for (auto itr = histo.begin(); itr != histo.end(); itr++){
            float value = ((float)(itr->second)/pixels_sum);
            CDF += value;
            new_level.insert({itr->first, round((float)CDF*255)});
         }

    for (int row = 0; row < output_image.rows; ++row) {
        for (int col = 0; col < output_image.cols; ++col) {
            output_image.at<uchar>(row, col) = new_level[image.at<uchar>(row, col)];
        }
    }

    return output_image;
}

void RGB_histo(Mat img, vector<double> barsPDF[6], vector<double> barsCDF[3]){
        vector<Mat> bgr_planes;
        split(img, bgr_planes);
        int CDFindex = 0;

        map<int, int> myMap;
        vector<string> col = {"b", "g", "r"};
        for(int i = 0; i < (int)bgr_planes.size(); i++){
            string cor = col[i];
            calculate_histogram(bgr_planes[i], myMap, barsCDF[CDFindex]);
            CDFindex++;
            for (auto itr = myMap.begin(); itr != myMap.end(); itr++){
                if(cor == "b"){
                    barsPDF[0].push_back(itr->first);
                    barsPDF[1].push_back(itr->second);
                }
                if(cor == "g"){
                    barsPDF[2].push_back(itr->first);
                    barsPDF[3].push_back(itr->second);
                }
                if(cor == "r"){
                    barsPDF[4].push_back(itr->first);
                    barsPDF[5].push_back(itr->second);
                }
            }
        }
    }

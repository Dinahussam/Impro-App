#include "Histogram.hpp"

void calculate_histogram (Mat img_grayscale, map<int, int>& histo, vector<int>& cumulative_histo){
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

    for (auto itr = histo.begin(); itr != histo.end(); itr++){
                int accumalator = 0;
                accumalator += int(itr->first);
                cumulative_histo.push_back(accumalator);
         }
}

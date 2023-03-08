#ifndef HISTOGRAM
#define HISTOGRAM

#include "Common.hpp"


void calculate_histogram (Mat img_grayscale, map<int, int>& histo, vector<int>& cumulative_histo);

#endif

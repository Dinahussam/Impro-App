#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#define COMMON_H

#include <QMainWindow>
#include <UI/gaussiannoiseparameters.h>
#include <UI/saltpepperparameters.h>
#include <UI/uniformnoiseparameters.h>
#include <UI/thresholdwindow.h>
#include <UI/cannyparameters.h>
#include <UI/qcustomplot.h>
#include <UI/clickablelabel.h>

#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <cmath>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core/core.hpp"

#include <QLabel>
#include <QImageReader>


using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImageReader reader;

// ------------ Filer/Noise/Threshold Output Images ----------------
    QImage *inputImageptr;
    QImage inputImage;


    Mat inputMat = Mat::zeros(1, 1, CV_64F);


    int kernalSize = 3;
    Mat filterOutputMat = Mat::zeros(1, 1, CV_64F);
    Mat edgeDetectionOutputMat = Mat::zeros(1, 1, CV_64F);

    int globalThresholdSliderValue = 0;
    Mat thresholdOutputMat = Mat::zeros(1, 1, CV_64F);
    Mat normalizedOutputMat = Mat::zeros(1, 1, CV_64F);
    Mat equalizedOutputMat = Mat::zeros(1, 1, CV_64F);

// ------------- Histogram variables ----------------------------------
    map <int,int> histoMap;
    vector<int> cummulativeHist;

    QList<double> x = QList<double>();
    QList<double> y = QList<double>();

// ------------- Hybrid variables ----------------------------------

    QImage hybridImage1;
    Mat hybridImage1Mat = Mat::zeros(1, 1, CV_64F);
    Mat freqImage1Mat = Mat::zeros(1, 1, CV_64F);
    int freqImage1Slider = 0;
    bool image1_H_L = true;


    QImage hybridImage2;
    Mat hybridImage2Mat = Mat::zeros(1, 1, CV_64F);
    Mat freqImage2Mat = Mat::zeros(1, 1, CV_64F);
    int freqImage2Slider = 0;
    bool image2_H_L = false;

    Mat finalHybridImageMat = Mat::zeros(1, 1, CV_64F);

// ------------- Active Contour variables ----------------------------------

    Mat activeContourOutputMat = Mat::zeros(1, 1, CV_64F);

    int radius = 1;
    int numIterations = 300;
    float alpha = 0;
    float beta = 1.0;
    float gamma = 0;

    int xCoordinate = 300;
    int yCoordinate = 300;


    Ui::MainWindow *ui;

    void updateImage(Mat &inputMat,  QLabel* image, bool rgb_flag);

private slots:

    void on_BrowseButton_clicked();

    void on_MedianFilterButton_clicked();

    void on_AverageFilterButton_clicked();

    void on_GrayScale_clicked();

    void on_GaussianFilterButton_clicked();

    void on_SaltPepperNoiseButton_clicked();

    void on_GaussianNoiseButton_clicked();

    void on_UniformNoiseButton_clicked();

    void on_prewittButton_clicked();

    void on_robertButton_clicked();

    void on_sobelButton_clicked();

    void on_cannyButton_clicked();

    void on_LocalThresholdButton_clicked();

    void on_GlobalThresholdButton_clicked();

    void on_GlobalThresholdSlider_valueChanged(int value);

// ----------------------- Histogram Tab ----------------
    void Histogram(Mat &inputMat,  QCustomPlot* HistWidget, String color, QColor brushColor, String graph_type);

    void initializeHistograms(QCustomPlot* HistWidget);

// ----------------------- Hybrid Tab -------------------
    void on_Image1FSlider_valueChanged(int value);

    void on_Image2FSlider_valueChanged(int value);

    void on_UploadeImage1_clicked();

    void on_UploadeImage2_clicked();

    void on_freqOutputImage1Slider_valueChanged(int value);

    void on_freqOutputImage2Slider_valueChanged(int value);

    void updateFrequencyResponse(Mat &inputMat, Mat &freqMat, QLabel* imageLabel, int sliderValue, int high_low_flag);

// --------------------- Helper Functions ----------------
    bool checkImage(QImage &image);

    void UploadImage(QImage &image, Mat &imageMat, bool flag);

    void on_HybridButton_clicked();

    void on_pushButton_clicked();



    void on_EqualizeButton_clicked();

    void on_NormalizeButton_clicked();

    void on_Radio3x3Kernal_clicked();

    void on_Radio5x5Kernal_clicked();



    void on_alphaSlider_valueChanged(int value);

    void on_betaSlider_valueChanged(int value);

    void on_gammaSlider_valueChanged(int value);

    void updateActiveContour(Mat &inputMat, Mat &outputMat);

    void on_contourRadiusSlider_valueChanged(int value);

private:

};

#endif // MAINWINDOW_H

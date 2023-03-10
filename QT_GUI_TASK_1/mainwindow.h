#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gaussiannoiseparameters.h>
#include <saltpepperparameters.h>
#include <uniformnoiseparameters.h>
#include <thresholdwindow.h>
#include <cannyparameters.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include <QLabel>
#include <QImageReader>

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
    QImage inputImage;
    Mat inputMat = Mat::zeros(1, 1, CV_64F);

    Mat filterOutputMat = Mat::zeros(1, 1, CV_64F);
    Mat edgeDetectionOutputMat = Mat::zeros(1, 1, CV_64F);
    Mat thresholdOutputMat = Mat::zeros(1, 1, CV_64F);

// ------------- Hybrid variables ----------------------------------

    QImage hybridImage1;
    Mat hybridImage1Mat = Mat::zeros(1, 1, CV_64F);
    Mat freqImage1Mat = Mat::zeros(1, 1, CV_64F);
    int freqImage1Slider;
    bool image1_H_L;


    QImage hybridImage2;
    Mat hybridImage2Mat = Mat::zeros(1, 1, CV_64F);
    Mat freqImage2Mat = Mat::zeros(1, 1, CV_64F);
    int freqImage2Slider;
    bool image2_H_L;

    Mat finalHybridImageMat = Mat::zeros(1, 1, CV_64F);





private slots:

    void on_BrowseButton_clicked();

    void on_MedianFilterButton_clicked();

    void on_AverageFilterButton_clicked();

    void on_GrayScale_clicked();

    void on_GaussianFilterButton_clicked();

    void on_SaltPepperNoiseButton_clicked();

    void on_GaussianNoiseButton_clicked();

    void on_UniformNoiseButton_clicked();

    void on_PrewittButton_clicked();

    void on_RobetButton_clicked();

    void on_SobelButton_clicked();

    void on_CannyButton_clicked();

    void on_LocalThresholdButton_clicked();

    void on_GlobalThresholdButton_clicked();

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

    void updateImage(Mat &inputMat,  QLabel* image, bool rgb_flag);

    void on_HybridButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

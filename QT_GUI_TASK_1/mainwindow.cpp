#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Noise/noise.hpp"
#include "Noise/remove_noise.hpp"
#include "Filters/gaussian.hpp"
#include "Filters/edge_detection.hpp"
#include "Frequency/frequency.hpp"
#include "Threshold/Thresholding.hpp"
#include "imageClass.hpp"


#include <QFileDialog>
#include <QImageReader>
#include <QImage>
#include <QPixmap>
#include <iostream>
#include <QMessageBox>

using namespace cv;
using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setDisabled(true);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_BrowseButton_clicked()
{
    UploadImage(inputImage, inputMat);

    Convert_To_Gray(inputMat, filterOutputMat);
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);


    updateImage(inputMat, ui->filter_inputImage, 1);
    updateImage(inputMat, ui->EdgeDetection_inputImage, 1);
    updateImage(inputMat, ui->Threshold_InputImage, 1);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}




// ----------------------------------------------------------- FILTERING & NOISE TAB -----------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_MedianFilterButton_clicked()
{
    if(checkImage(inputImage)) return;

    Add_Median_Filter(filterOutputMat, filterOutputMat);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);

}



void MainWindow::on_AverageFilterButton_clicked()
{
    if(checkImage(inputImage)) return;

    Add_Average_Filter(filterOutputMat, filterOutputMat);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}


void MainWindow::on_GrayScale_clicked()
{
    if(checkImage(inputImage)) return;

    cv::resize(inputMat, inputMat, cv::Size(512,512),0,0);
    Convert_To_Gray(inputMat, filterOutputMat);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}


void MainWindow::on_GaussianFilterButton_clicked()
{
    if(checkImage(inputImage)) return;

    filterOutputMat = Gaussian_Filter(filterOutputMat);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}


void MainWindow::on_SaltPepperNoiseButton_clicked()
{
    if(checkImage(inputImage)) return;

    SaltPepperParameters SaltPepperParameter;
    SaltPepperParameter.setModal(true);
    SaltPepperParameter.exec();

    if(SaltPepperParameter.flag) return;

    Add_Salt_And_Pepper_Noise(filterOutputMat, filterOutputMat, SaltPepperParameter.saltAndPepperAmount);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}


void MainWindow::on_GaussianNoiseButton_clicked()
{
    if(checkImage(inputImage)) return;

    GaussianNoiseParameters gaussianParameters;
    gaussianParameters.setModal(true);
    gaussianParameters.exec();

    if(gaussianParameters.flag) return;

    Add_Gaussian_Noise(filterOutputMat, filterOutputMat, gaussianParameters.gaussianMeanValue, gaussianParameters.gaussianSTDValue, gaussianParameters.noiseIntenisty);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}

void MainWindow::on_UniformNoiseButton_clicked()
{
    if(checkImage(inputImage)) return;

    UniformNoiseParameters uniformParameters;
    uniformParameters.setModal(true);
    uniformParameters.exec();

    if(uniformParameters.flag) return;

    Add_Uniform_Noise(filterOutputMat, filterOutputMat, uniformParameters.noiseIntenisty);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}





// ----------------------------------------------------------- EDGE DETECTION TAB ------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------


void MainWindow::on_PrewittButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Prewitt(edgeDetectionOutputMat);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}


void MainWindow::on_RobetButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Robert_Edge(edgeDetectionOutputMat);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}


void MainWindow::on_SobelButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Sobel(edgeDetectionOutputMat);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}


void MainWindow::on_CannyButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Canny(edgeDetectionOutputMat, 30, 70);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}







// ----------------------------------------------------------- THRESHOLD TAB ------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_LocalThresholdButton_clicked()
{
    if(checkImage(inputImage)) return;

    Convert_To_Gray(inputMat, thresholdOutputMat);
    local_adaptive_threshold(thresholdOutputMat, thresholdOutputMat);
    updateImage(thresholdOutputMat, ui->Threshold_OutputImage, 0);
}


void MainWindow::on_GlobalThresholdButton_clicked()
{
    if(checkImage(inputImage)) return;

    Convert_To_Gray(inputMat, thresholdOutputMat);

    ThresholdWindow thresholdInput;
    thresholdInput.setModal(true);
    thresholdInput.exec();

    if(thresholdInput.flag) return;

    global_threshold(thresholdOutputMat, thresholdOutputMat, thresholdInput.ThresholdValue);
    updateImage(thresholdOutputMat, ui->Threshold_OutputImage, 0);
}





// ----------------------------------------------------------- HYBRID FILTER TAB ------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_UploadeImage1_clicked()
{
    UploadImage(hybridImage1, hybridImage1Mat);
    updateFrequencyResponse(hybridImage1Mat, freqImage1Mat, ui->freqOutputImage1, freqImage1Slider, image1_H_L);
    updateImage(hybridImage1Mat, ui->hybridInputImage1, 1);
}


void MainWindow::on_UploadeImage2_clicked()
{
    UploadImage(hybridImage2, hybridImage2Mat);
    updateFrequencyResponse(hybridImage2Mat, freqImage2Mat, ui->freqOutputImage2, freqImage2Slider, image2_H_L);
    updateImage(hybridImage2Mat,  ui->hybridInputImage2, 1);
}

void MainWindow::on_Image1FSlider_valueChanged(int value)
{
    image1_H_L = value ^ 1;
    ui->Image2FSlider->setSliderPosition(image1_H_L);
}


void MainWindow::on_Image2FSlider_valueChanged(int value)
{
    image2_H_L = value ^ 1;
    ui->Image1FSlider->setSliderPosition(image2_H_L);
}

void MainWindow::on_freqOutputImage1Slider_valueChanged(int value)
{
    freqImage1Slider = value;
    updateFrequencyResponse(hybridImage1Mat, freqImage1Mat, ui->freqOutputImage1, freqImage1Slider, image1_H_L);

}

void MainWindow::on_freqOutputImage2Slider_valueChanged(int value)
{
    freqImage2Slider = value;
    updateFrequencyResponse(hybridImage2Mat, freqImage2Mat, ui->freqOutputImage2, freqImage2Slider, image2_H_L);
}


void MainWindow::on_HybridButton_clicked()
{
    finalHybridImageMat =  Apply_Hybrid_Images(freqImage1Mat, freqImage2Mat);
    updateImage(finalHybridImageMat,  ui->finalHybridImage, 0);
}





// ----------------------------------------------------------- HELPER FUNCTIONS ------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------

bool MainWindow::checkImage(QImage &image)
{
    if(image.isNull()){
        QMessageBox::information(this, "Image not uploaded", "Please upload image first!");
        return true;
    }
    else return false;
}


void MainWindow::UploadImage(QImage &image, Mat &imageMat)
{
    reader.setFileName(QFileDialog::getOpenFileName(this,tr("Open image")));
    image = reader.read();

    if(!image.isNull()){
    ui-> BrowseButton -> setText("Updated");
    ui-> BrowseButton -> setStyleSheet("QPushButton{border-radius: 10px; text-align: left; font: 900 12pt 'Segoe UI Black'; color: green} QPushButton:hover:!pressed{background-color: qlineargradient(x1: 0.5, y1: 1, x2: 0.5, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa)}");
    ui-> BrowseButton -> setDisabled(true);
    ui-> pushButton-> setDisabled(false);
    }

    image = image.convertToFormat(QImage::Format_BGR888);
    imageMat = Mat(image.height(), image.width(), CV_8UC3, image.bits(), image.bytesPerLine());


}

void MainWindow::on_pushButton_clicked()
{
    ui-> BrowseButton -> setText("Update Image");
    ui-> BrowseButton -> setStyleSheet("QPushButton{border-radius: 10px; text-align: left; font: 900 12pt 'Segoe UI Black';} QPushButton:hover:!pressed{background-color: qlineargradient(x1: 0.5, y1: 1, x2: 0.5, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa)}");
    ui->BrowseButton->setEnabled(true);
    ui->pushButton->setDisabled(true);
    ui->filter_inputImage->clear();
    ui->filter_outputImage->clear();
    ui->EdgeDetection_inputImage->clear();
    ui->EdgeDetection_outputImage->clear();
    ui->Threshold_InputImage->clear();
    ui->Threshold_OutputImage->clear();

}

void MainWindow::updateImage(Mat &inputMat,  QLabel* image, bool rgb_flag){

    if(rgb_flag){
        image->setPixmap(QPixmap::fromImage(QImage(inputMat.data, inputMat.cols, inputMat.rows, inputMat.step, QImage::Format_BGR888)));
    }
    else{
        image->setPixmap(QPixmap::fromImage(QImage(inputMat.data, inputMat.cols, inputMat.rows, inputMat.step, QImage::Format_Grayscale8)));
    }
}


void MainWindow::updateFrequencyResponse(Mat &inputMat, Mat &freqMat, QLabel* image, int sliderValue, int high_low_flag){
    Convert_To_Gray(inputMat, freqMat);
    freqMat = Add_Low_High_Frequency_Filter(freqMat, sliderValue, high_low_flag);
    image->setPixmap(QPixmap::fromImage(QImage(freqMat.data, freqMat.cols, freqMat.rows, freqMat.step, QImage::Format_Grayscale8)));
}

















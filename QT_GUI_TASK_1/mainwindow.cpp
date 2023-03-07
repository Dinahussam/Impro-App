#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Noise/noise.hpp"
#include "Noise/remove_noise.hpp"
#include "Filters/convolution.hpp"
#include "Filters/gaussian.hpp"
#include "Filters/prewitt.hpp"
#include "Filters/robert.hpp"
#include "Filters/sobel.hpp"
#include "imageClass.hpp"


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include <QFileDialog>
#include <QImageReader>
#include <QImage>
#include <QPixmap>
#include <iostream>
#include <QMessageBox>

using namespace cv;
using namespace std;

QImage inputImage;
Mat inputMat = Mat::zeros(1, 1, CV_64F);

Mat filterOutputMat = Mat::zeros(1, 1, CV_64F);
Mat edgeDetectionOutputMat = Mat::zeros(1, 1, CV_64F);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BrowseButton_clicked()
{
    QImageReader reader;

        reader.setFileName(QFileDialog::getOpenFileName(this,tr("Open image")));
        inputImage= reader.read();

        if(checkImage()) return;

        inputImage = inputImage.convertToFormat(QImage::Format_BGR888);
        inputMat = Mat(inputImage.height(), inputImage.width(), CV_8UC3, inputImage.bits(), inputImage.bytesPerLine());

        Convert_To_Gray(inputMat, filterOutputMat);
        Convert_To_Gray(inputMat, edgeDetectionOutputMat);


        ui->filter_inputImage->setPixmap(QPixmap::fromImage(QImage(inputMat.data, inputMat.cols, inputMat.rows, inputMat.step, QImage::Format_BGR888)));
        ui->EdgeDetection_inputImage->setPixmap(QPixmap::fromImage(QImage(inputMat.data, inputMat.cols, inputMat.rows, inputMat.step, QImage::Format_BGR888)));

        ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));

}


void MainWindow::on_MedianFilterButton_clicked()
{
    if(checkImage()) return;


    Add_Median_Filter(filterOutputMat, filterOutputMat);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));

}



void MainWindow::on_AverageFilterButton_clicked()
{
    if(checkImage()) return;

    Add_Average_Filter(filterOutputMat, filterOutputMat);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));
}


void MainWindow::on_GrayScale_clicked()
{
    if(checkImage()) return;

    cv::resize(inputMat, inputMat, cv::Size(512,512),0,0);
    Convert_To_Gray(inputMat, filterOutputMat);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));

}


void MainWindow::on_GaussianFilterButton_clicked()
{
    if(checkImage()) return;

    filterOutputMat = Gaussian_Filter(filterOutputMat);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));
}


void MainWindow::on_SaltPepperNoiseButton_clicked()
{
    if(checkImage()) return;

    SaltPepperParameters SaltPepperParameter;
    SaltPepperParameter.setModal(true);
    SaltPepperParameter.exec();

    Add_Salt_And_Pepper_Noise(filterOutputMat, filterOutputMat, SaltPepperParameter.saltAndPepperAmount);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));

}


void MainWindow::on_GaussianNoiseButton_clicked()
{
    if(checkImage()) return;

    GaussianNoiseParameters gaussianParameters;
    gaussianParameters.setModal(true);
    gaussianParameters.exec();

    Add_Gaussian_Noise(filterOutputMat, filterOutputMat, gaussianParameters.gaussianMeanValue, gaussianParameters.gaussianSTDValue, gaussianParameters.noiseIntenisty);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));
}

void MainWindow::on_UniformNoiseButton_clicked()
{
    if(checkImage()) return;

    UniformNoiseParameters uniformParameters;
    uniformParameters.setModal(true);
    uniformParameters.exec();

    Add_Uniform_Noise(filterOutputMat, filterOutputMat, uniformParameters.thresholdValue, uniformParameters.noiseIntenisty);
    ui->filter_outputImage->setPixmap(QPixmap::fromImage(QImage(filterOutputMat.data, filterOutputMat.cols, filterOutputMat.rows, filterOutputMat.step, QImage::Format_Grayscale8)));
}

bool MainWindow::checkImage(){
    if(inputImage.isNull()){
        QMessageBox::information(this, "Image not uploaded", "Please upload image first!");
        return true;
    }
    else return false;
}




void MainWindow::on_PrewittButton_clicked()
{
    if(checkImage()) return;


}




void MainWindow::on_RobetButton_clicked()
{
    if(checkImage()) return;

    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Robert_Edge(edgeDetectionOutputMat);
    ui->EdgeDetection_outputImage->setPixmap(QPixmap::fromImage(QImage(edgeDetectionOutputMat.data, edgeDetectionOutputMat.cols, edgeDetectionOutputMat.rows, edgeDetectionOutputMat.step, QImage::Format_Grayscale8)));
}


void MainWindow::on_SobelButton_clicked()
{
    if(checkImage()) return;

    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Sobel(edgeDetectionOutputMat);
    ui->EdgeDetection_outputImage->setPixmap(QPixmap::fromImage(QImage(edgeDetectionOutputMat.data, edgeDetectionOutputMat.cols, edgeDetectionOutputMat.rows, edgeDetectionOutputMat.step, QImage::Format_Grayscale8)));
}


#include "mainwindow.h"
#include "ui_mainwindow.h"



#include "Filters/add_noise.hpp"
#include "Filters/remove_noise.hpp"
#include "Filters/edge_detection.hpp"

#include "Frequency/frequency.hpp"
#include "Threshold/Thresholding.hpp"
#include "Histogram/Histogram.hpp"
#include "ActiveContour/activecontour.h"

#include <iostream>
#include <QFileDialog>
#include <QImageReader>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->pushButton->setDisabled(true);

    initializeHistograms(ui->RedHistPDF);
    initializeHistograms(ui->RedHistCDF);
    initializeHistograms(ui->BlueHistPDF);
    initializeHistograms(ui->BlueHistCDF);
    initializeHistograms(ui->GreenHistPDF);
    initializeHistograms(ui->GreenHistCDF);

    ui->EqualizeImage->setHidden(true);
    ui->GlobalThresholdSlider->setHidden(true);


}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_BrowseButton_clicked()
{
    UploadImage(inputImage, inputMat, true);

    if(inputImage.isNull()) return;

    Convert_To_Gray(inputMat, filterOutputMat);
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);



    Histogram(inputMat, ui->RedHistPDF, "red", Qt::red, "PDF");
    Histogram(inputMat, ui->RedHistCDF, "red", Qt::red, "CDF");
    Histogram(inputMat, ui->BlueHistPDF, "blue", Qt::blue, "PDF");
    Histogram(inputMat, ui->BlueHistCDF, "blue", Qt::blue, "CDF");
    Histogram(inputMat, ui->GreenHistPDF, "green", Qt::green, "PDF");
    Histogram(inputMat, ui->GreenHistCDF, "green", Qt::green, "CDF");


    updateImage(inputMat, ui->filter_inputImage, 1);
    updateImage(inputMat, ui->EdgeDetection_inputImage, 1);
    updateImage(inputMat, ui->Threshold_InputImage, 1);
    updateImage(inputMat, ui->activeContourInputImage, 1);

    updateImage(inputMat, ui->activeContourOutputImage, 1);

    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}



// ------------------------------------------------ FILTERING & NOISE TAB --------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------


/*******************************************************************************
 *                                Filtering                                    *
 *******************************************************************************/


void MainWindow::on_GrayScale_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, filterOutputMat);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);

}


void MainWindow::on_MedianFilterButton_clicked()
{
    if(checkImage(inputImage)) return;

    Add_Median_Filter(filterOutputMat, filterOutputMat, kernalSize);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);

}


void MainWindow::on_AverageFilterButton_clicked()
{
    if(checkImage(inputImage)) return;

    Add_Average_Filter(filterOutputMat, filterOutputMat, kernalSize);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}

void MainWindow::on_GaussianFilterButton_clicked()
{
    if(checkImage(inputImage)) return;

    filterOutputMat = Gaussian_Filter(filterOutputMat, kernalSize);
    updateImage(filterOutputMat, ui->filter_outputImage, 0);
}


/*******************************************************************************
 *                                Noise                                        *
 *******************************************************************************/

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

    cout << gaussianParameters.noiseIntenisty << endl;
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

void MainWindow::on_Radio3x3Kernal_clicked()
{
    kernalSize = 3;
}


void MainWindow::on_Radio5x5Kernal_clicked()
{
    kernalSize = 5;
}


// ----------------------------------------------------------- EDGE DETECTION TAB ------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------


void MainWindow::on_prewittButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Prewitt(edgeDetectionOutputMat);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}


void MainWindow::on_robertButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Robert(edgeDetectionOutputMat);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}


void MainWindow::on_sobelButton_clicked()
{
    if(checkImage(inputImage)) return;
    Convert_To_Gray(inputMat, edgeDetectionOutputMat);



    edgeDetectionOutputMat = Detect_Edges_Sobel(edgeDetectionOutputMat);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}


void MainWindow::on_cannyButton_clicked()
{
    if(checkImage(inputImage)) return;

    CannyParameters cannyParameters;
    cannyParameters.setModal(true);
    cannyParameters.exec();

    if(cannyParameters.flag) return;

    Convert_To_Gray(inputMat, edgeDetectionOutputMat);
    edgeDetectionOutputMat = Detect_Edges_Canny(edgeDetectionOutputMat, cannyParameters.LowThresholdValue, cannyParameters.HighThresholdValue);
    updateImage(edgeDetectionOutputMat, ui->EdgeDetection_outputImage, 0);
}







// ----------------------------------------------------------- THRESHOLD TAB ------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------



/*******************************************************************************
 *                                Local Threshold                              *
 *******************************************************************************/
void MainWindow::on_LocalThresholdButton_clicked()
{
    if(checkImage(inputImage)) return;
    ui->EqualizeImage->setHidden(true);
    ui->GlobalThresholdSlider->setHidden(true);

    Convert_To_Gray(inputMat, thresholdOutputMat);
    local_adaptive_threshold(thresholdOutputMat, thresholdOutputMat);
    updateImage(thresholdOutputMat, ui->Threshold_OutputImage, 0);


}

/*******************************************************************************
 *                               Global Threshold                              *
 *******************************************************************************/
void MainWindow::on_GlobalThresholdButton_clicked()
{
    if(checkImage(inputImage)) return;

    ui->EqualizeImage->setHidden(true);
    ui->GlobalThresholdSlider->setHidden(false);

    Convert_To_Gray(inputMat, thresholdOutputMat);


    thresholdOutputMat = global_threshold(thresholdOutputMat, thresholdOutputMat, globalThresholdSliderValue);
    updateImage(thresholdOutputMat, ui->Threshold_OutputImage, 0);

}

void MainWindow::on_GlobalThresholdSlider_valueChanged(int value)
{
    Convert_To_Gray(inputMat, thresholdOutputMat);

    globalThresholdSliderValue = value;
    thresholdOutputMat = global_threshold(thresholdOutputMat, thresholdOutputMat, globalThresholdSliderValue);

    updateImage(thresholdOutputMat, ui->Threshold_OutputImage, 0);
}

/*******************************************************************************
 *                               Normalization                                 *
 *******************************************************************************/

void MainWindow::on_NormalizeButton_clicked()
{
    if(checkImage(inputImage)) return;

    ui->EqualizeImage->setHidden(true);
    ui->GlobalThresholdSlider->setHidden(true);

    Convert_To_Gray(inputMat, normalizedOutputMat);
    normalizedOutputMat = normalize_image(normalizedOutputMat);
    updateImage(normalizedOutputMat, ui->Threshold_OutputImage, 0);
}


/*******************************************************************************
 *                               Equalization                                  *
 *******************************************************************************/
void MainWindow::on_EqualizeButton_clicked()
{
    if(checkImage(inputImage)) return;

    ui->EqualizeImage->setHidden(false);
    ui->GlobalThresholdSlider->setHidden(true);

    Convert_To_Gray(inputMat, equalizedOutputMat);
    equalizedOutputMat = Equalize_img(equalizedOutputMat);
    updateImage(equalizedOutputMat, ui->Threshold_OutputImage, 0);


    Histogram(equalizedOutputMat, ui->EqualizeImage, "blue", Qt::black, "PDF");

}


// ----------------------------------------------------------- HISTOGRAM FUNCTIONS ---------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------

void MainWindow::Histogram(Mat &inputMat, QCustomPlot* HistWidget, String color, QColor brushColor, String graph_type){

    vector<double> barsPDF[6];
    vector<double> barsCDF[3];

    RGB_histo(inputMat, barsPDF, barsCDF);


    QList<double> x = QList<double>();
    QList<double> y = QList<double>();


    if(color == "blue" && graph_type == "PDF"){
        x.reserve(barsPDF[0].size());
        std::copy(barsPDF[0].begin(), barsPDF[0].end(), std::back_inserter(x));
        y.reserve(barsPDF[1].size());
        std::copy(barsPDF[1].begin(), barsPDF[1].end(), std::back_inserter(y));
    }
    else if(color == "green" && graph_type == "PDF"){
        x.reserve(barsPDF[2].size());
        std::copy(barsPDF[2].begin(), barsPDF[2].end(), std::back_inserter(x));
        y.reserve(barsPDF[3].size());
        std::copy(barsPDF[3].begin(), barsPDF[3].end(), std::back_inserter(y));
    }
    else if(color == "red" && graph_type == "PDF"){
        x.reserve(barsPDF[4].size());
        std::copy(barsPDF[4].begin(), barsPDF[4].end(), std::back_inserter(x));
        y.reserve(barsPDF[5].size());
        std::copy(barsPDF[5].begin(), barsPDF[5].end(), std::back_inserter(y));
    }
    else if(color == "blue" && graph_type == "CDF"){
        x.reserve(barsPDF[0].size());
        std::copy(barsPDF[0].begin(), barsPDF[0].end(), std::back_inserter(x));
        y.reserve(barsCDF[0].size());
        std::copy(barsCDF[0].begin(), barsCDF[0].end(), std::back_inserter(y));
    }
    else if(color == "green" && graph_type == "CDF"){
        x.reserve(barsPDF[2].size());
        std::copy(barsPDF[2].begin(), barsPDF[2].end(), std::back_inserter(x));
        y.reserve(barsCDF[1].size());
        std::copy(barsCDF[1].begin(), barsCDF[1].end(), std::back_inserter(y));
    }
    else if(color == "red" && graph_type == "CDF"){
        x.reserve(barsPDF[4].size());
        std::copy(barsPDF[4].begin(), barsPDF[4].end(), std::back_inserter(x));
        y.reserve(barsCDF[2].size());
        std::copy(barsCDF[2].begin(), barsCDF[2].end(), std::back_inserter(y));
    }



    QCPBars *barsPDFChart = new QCPBars( HistWidget->xAxis, HistWidget->yAxis);
    barsPDFChart->setWidth(9/(double)x.size());
    barsPDFChart->setData(x, y);
    barsPDFChart->setPen(QPen(brushColor));
    barsPDFChart->setBrush(brushColor);

    HistWidget->yAxis->setRange(0, *(max_element(y.begin(),y.end())));
    HistWidget->xAxis->setRange(0, 260);

    HistWidget->replot();
}


void MainWindow::initializeHistograms(QCustomPlot* HistWidget){


    // set some pens, brushes and backgrounds:
     HistWidget->xAxis->setBasePen(QPen(Qt::black, 1));
     HistWidget->yAxis->setBasePen(QPen(Qt::black, 1));
     HistWidget->xAxis->setTickPen(QPen(Qt::black, 1));
     HistWidget->yAxis->setTickPen(QPen(Qt::black, 1));
     HistWidget->xAxis->setSubTickPen(QPen(Qt::black, 1));
     HistWidget->yAxis->setSubTickPen(QPen(Qt::black, 1));
     HistWidget->xAxis->setTickLabelColor(Qt::black);
     HistWidget->yAxis->setTickLabelColor(Qt::black);
     HistWidget->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
     HistWidget->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
     HistWidget->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
     HistWidget->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
     HistWidget->xAxis->grid()->setSubGridVisible(true);
     HistWidget->yAxis->grid()->setSubGridVisible(true);
     HistWidget->xAxis->grid()->setZeroLinePen(Qt::NoPen);
     HistWidget->yAxis->grid()->setZeroLinePen(Qt::NoPen);
     HistWidget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
     HistWidget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);


    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, Qt::white);
    plotGradient.setColorAt(1, QColor(127,127,127));
    HistWidget->setBackground(plotGradient);
    HistWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}



// ----------------------------------------------------------- HYBRID FILTER TAB ------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_UploadeImage1_clicked()
{
    UploadImage(hybridImage1, hybridImage1Mat, false);
    if(hybridImage1.isNull()) return;

    updateFrequencyResponse(hybridImage1Mat, freqImage1Mat, ui->freqOutputImage1, freqImage1Slider, image1_H_L);
    updateImage(hybridImage1Mat, ui->hybridInputImage1, 1);
}


void MainWindow::on_UploadeImage2_clicked()
{
    UploadImage(hybridImage2, hybridImage2Mat, false);
    if(hybridImage2.isNull()) return;

    updateFrequencyResponse(hybridImage2Mat, freqImage2Mat, ui->freqOutputImage2, freqImage2Slider, image2_H_L);
    updateImage(hybridImage2Mat,  ui->hybridInputImage2, 1);
}


/*******************************************************************************
 *                               UI_Slider Output                              *
 *******************************************************************************/
void MainWindow::on_Image1FSlider_valueChanged(int value)
{
    image2_H_L = value ^ 1;
    ui->Image2FSlider->setSliderPosition(image2_H_L);

    if(hybridImage1.isNull()) return;
    updateFrequencyResponse(hybridImage1Mat, freqImage1Mat, ui->freqOutputImage1, freqImage1Slider, value);
}


void MainWindow::on_Image2FSlider_valueChanged(int value)
{
    image1_H_L = value ^ 1;
    ui->Image1FSlider->setSliderPosition(image1_H_L);

    if(hybridImage2.isNull()) return;
    updateFrequencyResponse(hybridImage2Mat, freqImage2Mat, ui->freqOutputImage2, freqImage2Slider, value);
}

void MainWindow::on_freqOutputImage1Slider_valueChanged(int value)
{
    freqImage1Slider = value;

    if(hybridImage1.isNull()) return;
    updateFrequencyResponse(hybridImage1Mat, freqImage1Mat, ui->freqOutputImage1, freqImage1Slider, image1_H_L);

}

void MainWindow::on_freqOutputImage2Slider_valueChanged(int value)
{
    freqImage2Slider = value;

    if(hybridImage2.isNull()) return;
    updateFrequencyResponse(hybridImage2Mat, freqImage2Mat, ui->freqOutputImage2, freqImage2Slider, image2_H_L);
}


void MainWindow::on_HybridButton_clicked()
{
    if(hybridImage2.isNull() && hybridImage1.isNull()) return;
    finalHybridImageMat =  Apply_Hybrid_Images(freqImage1Mat, freqImage2Mat, image1_H_L);
    updateImage(finalHybridImageMat,  ui->finalHybridImage, 0);
}

// ----------------------------------------------------------- Active Contour Tab ------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------



void MainWindow::on_alphaSlider_valueChanged(int value)
{
    alpha = value/10.0;

    if(inputImage.isNull()) return;
    updateActiveContour(inputMat, activeContourOutputMat);

}


void MainWindow::on_betaSlider_valueChanged(int value)
{
    beta = value/10.0;

    if(inputImage.isNull()) return;
    updateActiveContour(inputMat, activeContourOutputMat);
}


void MainWindow::on_gammaSlider_valueChanged(int value)
{
    gamma = value/10.0;

    if(inputImage.isNull()) return;
    updateActiveContour(inputMat, activeContourOutputMat);
}

void MainWindow::on_contourRadiusSlider_valueChanged(int value)
{
    radius = value;

    if(inputImage.isNull()) return;
    updateActiveContour(inputMat, activeContourOutputMat);
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


void MainWindow::UploadImage(QImage &image, Mat &imageMat, bool flag)
{
    reader.setFileName(QFileDialog::getOpenFileName(this,tr("Open image")));
    image = reader.read();

    if(!image.isNull() && flag){
    ui-> BrowseButton -> setText("Uploaded");
    ui-> BrowseButton -> setStyleSheet("QPushButton{border-radius: 10px; text-align: left; font: 900 12pt 'Segoe UI Black'; color: green} QPushButton:hover:!pressed{background-color: qlineargradient(x1: 0.5, y1: 1, x2: 0.5, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa)}");
    ui-> BrowseButton -> setDisabled(true);
    ui-> pushButton-> setDisabled(false);
    }

    image = image.convertToFormat(QImage::Format_BGR888);
    imageMat = Mat(image.height(), image.width(), CV_8UC3, image.bits(), image.bytesPerLine());

    if(image.isNull()) return;
    cv::resize(imageMat, imageMat, cv::Size(512,512), 0, 0);


}

void MainWindow::on_pushButton_clicked()
{
    inputImage =  QImage();
    ui-> BrowseButton -> setText("Upload Image");
    ui-> BrowseButton -> setStyleSheet("QPushButton{border-radius: 10px; text-align: left; font: 900 12pt 'Segoe UI Black';} QPushButton:hover:!pressed{background-color: qlineargradient(x1: 0.5, y1: 1, x2: 0.5, y2: 1, stop: 0 #dadbde, stop: 1 #f6f7fa)}");
    ui->BrowseButton->setEnabled(true);
    ui->pushButton->setDisabled(true);

    ui->filter_inputImage->clear();
    ui->filter_outputImage->clear();

    ui->EdgeDetection_inputImage->clear();
    ui->EdgeDetection_outputImage->clear();

    ui->Threshold_InputImage->clear();
    ui->Threshold_OutputImage->clear();

    ui->RedHistPDF->clearPlottables(); ui->RedHistPDF->replot();
    ui->RedHistCDF->clearPlottables(); ui->RedHistCDF->replot();

    ui->BlueHistPDF->clearPlottables(); ui->BlueHistPDF->replot();
    ui->BlueHistCDF->clearPlottables(); ui->BlueHistCDF->replot();

    ui->GreenHistPDF->clearPlottables();ui->GreenHistPDF->replot();
    ui->GreenHistCDF->clearPlottables(); ui->GreenHistCDF->replot();

    ui->EqualizeImage->setHidden(true);
    ui->GlobalThresholdSlider->setHidden(true);

    ui->activeContourInputImage->clear();
    ui->activeContourOutputImage->clear();

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

void MainWindow::updateActiveContour(Mat &inputMat, Mat &outputMat){

    active_Contour_Model(inputMat, outputMat, Point(xCoordinate, yCoordinate), radius, numIterations, alpha, beta, gamma);
    updateImage(outputMat, ui->activeContourOutputImage, 1);
}




















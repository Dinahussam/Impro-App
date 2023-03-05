#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Noise/noise.hpp"
#include "Noise/remove_noise.hpp"
#include "imageClass.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include <QFileDialog>
#include <QImageReader>
#include <QImage>
#include <iostream>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mat original_image;
}

MainWindow::~MainWindow()
{
    delete ui;
}


//void Convert_To_Gray(const Mat &src, Mat &dst)
//{
//    int rows = src.rows, cols = src.cols;

//    dst.create(src.size(), 0);

//    cols = rows * cols;
//    rows = 1;

//    for (int row = 0; row < rows; row++)
//    {
//        const uchar* src_ptr = src.ptr<uchar>(row);
//        uchar* dst_ptr = dst.ptr<uchar>(row);

//        for (int col = 0; col < cols; col++)
//        {
//            dst_ptr[col] = (uchar)(src_ptr[0] * 0.114f + src_ptr[1] * 0.587f + src_ptr[2] * 0.299f);
//            src_ptr += 3;
//        }
//    }
//}

void MainWindow::on_BrowseButton_clicked()
{
    QImageReader reader;

    reader.setFileName(QFileDialog::getOpenFileName(this,tr("Open image")));
    QImage q_image = reader.read();
    q_image = q_image.convertToFormat(QImage::Format_BGR888);
    ImageClass::original_image = Mat(q_image.height(), q_image.width(), CV_8UC3, q_image.bits(), q_image.bytesPerLine());
//    Mat image2;
    Convert_To_Gray(ImageClass::original_image, ImageClass::gray_original_image);
//    Add_Salt_And_Pepper_Noise(image2, image2, 0.1);
    imshow("Display", ImageClass::gray_original_image);
    ui->InputImage->setPixmap(QPixmap::fromImage(QImage(ImageClass::original_image.data, ImageClass::original_image.cols, ImageClass::original_image.rows, ImageClass::original_image.step, QImage::Format_BGR888)));
    ui->InputImage->adjustSize();
    ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(ImageClass::gray_original_image.data, ImageClass::gray_original_image.cols, ImageClass::gray_original_image.rows, ImageClass::gray_original_image.step, QImage::Format_Grayscale8)));
    ui->OutputImage->adjustSize();
}

void MainWindow::on_AddNoise_activated(int index)
{
    Mat edited_image;
    switch (index) {
    case 0:
        Add_Salt_And_Pepper_Noise(ImageClass::gray_original_image, edited_image, 0.1);
        ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(edited_image.data, edited_image.cols, edited_image.rows, edited_image.step, QImage::Format_Grayscale8)));
        ui->OutputImage->adjustSize();
        break;
    case 1:
        Add_Gaussian_Noise(ImageClass::gray_original_image, edited_image, 120, 25, 0.5);
        ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(edited_image.data, edited_image.cols, edited_image.rows, edited_image.step, QImage::Format_Grayscale8)));
        ui->OutputImage->adjustSize();
        break;
    case 2:
        Add_Uniform_Noise(ImageClass::gray_original_image, edited_image, 128, 0.5);
        ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(edited_image.data, edited_image.cols, edited_image.rows, edited_image.step, QImage::Format_Grayscale8)));
        ui->OutputImage->adjustSize();
        break;
    }
}


void MainWindow::on_RemoveNoise_activated(int index)
{
    Mat filtered_image;
    switch (index) {
    case 0:
        Add_Median_Filter(ImageClass::gray_original_image, filtered_image);
        ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(filtered_image.data, filtered_image.cols, filtered_image.rows, filtered_image.step, QImage::Format_Grayscale8)));
        ui->OutputImage->adjustSize();
        break;
    case 1:
        gaussian_Filter(ImageClass::gray_original_image, filtered_image);
        ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(filtered_image.data, filtered_image.cols, filtered_image.rows, filtered_image.step, QImage::Format_Grayscale8)));
        ui->OutputImage->adjustSize();
        break;
    case 2:
        Add_Average_Filter(ImageClass::gray_original_image, filtered_image);
        ui->OutputImage->setPixmap(QPixmap::fromImage(QImage(filtered_image.data, filtered_image.cols, filtered_image.rows, filtered_image.step, QImage::Format_Grayscale8)));
        ui->OutputImage->adjustSize();
        break;
    default:
        break;
    }

}


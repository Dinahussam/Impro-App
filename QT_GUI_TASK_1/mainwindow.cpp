#include "mainwindow.h"
#include "ui_mainwindow.h"


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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void Convert_To_Gray(const Mat &src, Mat &dst)
{
    int rows = src.rows, cols = src.cols;

    dst.create(src.size(), 0);

    cols = rows * cols;
    rows = 1;

    for (int row = 0; row < rows; row++)
    {
        const uchar* src_ptr = src.ptr<uchar>(row);
        uchar* dst_ptr = dst.ptr<uchar>(row);

        for (int col = 0; col < cols; col++)
        {
            dst_ptr[col] = (uchar)(src_ptr[0] * 0.114f + src_ptr[1] * 0.587f + src_ptr[2] * 0.299f);
            src_ptr += 3;
        }
    }
}

void MainWindow::on_BrowseButton_clicked()
{
    QImageReader reader;

    reader.setFileName(QFileDialog::getOpenFileName(this,tr("Open image")));
    QImage q_image = reader.read();
    q_image = q_image.convertToFormat(QImage::Format_BGR888);
    cv::Mat image_mat(q_image.height(), q_image.width(), CV_8UC3, q_image.bits(), q_image.bytesPerLine());
    Mat image2;
    Convert_To_Gray(image_mat, image2);
    imshow("Display", image2);
    ui->InputImage->setPixmap(QPixmap::fromImage(QImage(image2.data, image2.cols, image2.rows, image2.step, QImage::Format_Grayscale8)));
    ui->InputImage->adjustSize();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Noise\remove_noise.hpp"

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


void MainWindow::on_pushButton_clicked()
{
    Mat image;
    Mat image2;
    Mat image3;
    Mat AvgFilterImg;
    Mat GaussianFilterImg;
// --------------------------------------- Img Read ---------------------------------------
    image = imread("C:\\Users\\Omar Saad\\Documents\\GitHub\\CV_task1_team15\\Images\\sudoku.png");

/* If image not found */
    if (!image.data)
        {
        cout << "No image data \n";
//        return -1;
        }

    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);

}


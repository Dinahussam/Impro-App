#include "thresholdwindow.h"
#include "ui_thresholdwindow.h"
#include "QMessageBox"

ThresholdWindow::ThresholdWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdWindow)
{
    ui->setupUi(this);
}

ThresholdWindow::~ThresholdWindow()
{
    if(ui->ThresholdValue->text().isEmpty()) {
        flag = true;
    }
    delete ui;
}

void ThresholdWindow::on_pushButton_clicked()
{
    if(ui->ThresholdValue->text().isEmpty()) {
        QMessageBox::information(this, "Warning", "Please enter all the fields before applying!");
    }
    else{
        ThresholdValue = ui->ThresholdValue->text().toInt();
        flag = false;
        this->close();
    }
}


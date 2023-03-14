#include "cannyparameters.h"
#include "ui_cannyparameters.h"
#include <QMessageBox>

CannyParameters::CannyParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CannyParameters)
{
    ui->setupUi(this);
}

CannyParameters::~CannyParameters()
{
    if(ui->HighThresholdValue->text().isEmpty() || ui->LowThresholdValue->text().isEmpty()) {
        flag = true;
    }
    delete ui;
}

void CannyParameters::on_pushButton_clicked()
{
    if(ui->HighThresholdValue->text().isEmpty() || ui->LowThresholdValue->text().isEmpty()) {
        QMessageBox::information(this, "Warning", "Please enter all the fields before applying!");
    }
    else{
        HighThresholdValue = ui->HighThresholdValue->text().toFloat();
        LowThresholdValue = ui->LowThresholdValue->text().toFloat();
        flag = false;
        this->close();
    }
}


#include "gaussiannoiseparameters.h"
#include "ui_gaussiannoiseparameters.h"

#include <QtGui>
#include <QtCore>
#include <QMessageBox>



GaussianNoiseParameters::GaussianNoiseParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianNoiseParameters)
{
    ui->setupUi(this);
}

GaussianNoiseParameters::~GaussianNoiseParameters()
{
    delete ui;
}

void GaussianNoiseParameters::on_pushButton_clicked()
{
    if(ui->GaussianMeanValue->text().isEmpty() || ui->GaussianSTDValue->text().isEmpty() || ui->NoiseIntenistyValue->text().isEmpty()) {
        QMessageBox::information(this, "Warning", "Please enter all the fields before applying!");
    }
    else{
        gaussianMeanValue = ui->GaussianMeanValue->text().toInt();
        gaussianSTDValue = ui->GaussianSTDValue->text().toInt();
        noiseIntenisty = ui ->NoiseIntenistyValue->text().toInt();

        this->close();
    }

}


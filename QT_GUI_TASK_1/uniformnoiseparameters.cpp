#include "uniformnoiseparameters.h"
#include "ui_uniformnoiseparameters.h"
#include <QMessageBox>>

UniformNoiseParameters::UniformNoiseParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UniformNoiseParameters)
{
    ui->setupUi(this);
}

UniformNoiseParameters::~UniformNoiseParameters()
{
    delete ui;
}

void UniformNoiseParameters::on_pushButton_clicked()
{

    if(ui->NoiseIntensity->text().isEmpty() || ui->Threshold->text().isEmpty()) {
        QMessageBox::information(this, "Warning", "Please enter all the fields before applying!");
    }
    else{
        thresholdValue = ui->Threshold->text().toInt();
        noiseIntenisty = ui->NoiseIntensity->text().toFloat();
        this->close();
    }

}


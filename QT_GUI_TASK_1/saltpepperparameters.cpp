#include "saltpepperparameters.h"
#include "ui_saltpepperparameters.h"
#include <QMessageBox>

SaltPepperParameters::SaltPepperParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaltPepperParameters)
{
    ui->setupUi(this);
}

SaltPepperParameters::~SaltPepperParameters()
{
    if(ui->SaltandPepperAmount->text().isEmpty()) {
        flag = true;
    }
    delete ui;
}

void SaltPepperParameters::on_pushButton_clicked()
{
    if(ui->SaltandPepperAmount->text().isEmpty()) {
        QMessageBox::information(this, "Warning", "Please enter all the fields before applying!");
    }
    else{
        saltAndPepperAmount = ui->SaltandPepperAmount->text().toFloat();
        flag = false;
        this->close();
    }
}


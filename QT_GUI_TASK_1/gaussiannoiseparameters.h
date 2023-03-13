#ifndef GAUSSIANNOISEPARAMETERS_H
#define GAUSSIANNOISEPARAMETERS_H

#include <QDialog>

namespace Ui {
class GaussianNoiseParameters;
}

class GaussianNoiseParameters : public QDialog
{
    Q_OBJECT

public:
    explicit GaussianNoiseParameters(QWidget *parent = nullptr);
    ~GaussianNoiseParameters();

    int gaussianMeanValue;
    int gaussianSTDValue;
    float noiseIntenisty;
    bool flag;

private slots:
    void on_pushButton_clicked();

private:
    Ui::GaussianNoiseParameters *ui;
};

#endif // GAUSSIANNOISEPARAMETERS_H

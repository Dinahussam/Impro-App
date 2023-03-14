#ifndef UNIFORMNOISEPARAMETERS_H
#define UNIFORMNOISEPARAMETERS_H

#include <QDialog>

namespace Ui {
class UniformNoiseParameters;
}

class UniformNoiseParameters : public QDialog
{
    Q_OBJECT

public:
    explicit UniformNoiseParameters(QWidget *parent = nullptr);
    ~UniformNoiseParameters();

    int thresholdValue;
    float noiseIntenisty;
    bool flag;

private slots:
    void on_pushButton_clicked();

private:
    Ui::UniformNoiseParameters *ui;
};

#endif // UNIFORMNOISEPARAMETERS_H

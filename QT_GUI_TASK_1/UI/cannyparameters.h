#ifndef CANNYPARAMETERS_H
#define CANNYPARAMETERS_H

#include <QDialog>

namespace Ui {
class CannyParameters;
}

class CannyParameters : public QDialog
{
    Q_OBJECT

public:
    explicit CannyParameters(QWidget *parent = nullptr);
    ~CannyParameters();
    float LowThresholdValue;
    float HighThresholdValue;
    bool flag;

private slots:
    void on_pushButton_clicked();

private:
    Ui::CannyParameters *ui;
};

#endif // CANNYPARAMETERS_H

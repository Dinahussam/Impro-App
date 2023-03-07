#ifndef SALTPEPPERPARAMETERS_H
#define SALTPEPPERPARAMETERS_H

#include <QDialog>

namespace Ui {
class SaltPepperParameters;
}

class SaltPepperParameters : public QDialog
{
    Q_OBJECT

public:
    explicit SaltPepperParameters(QWidget *parent = nullptr);
    ~SaltPepperParameters();

    float saltAndPepperAmount;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SaltPepperParameters *ui;
};

#endif // SALTPEPPERPARAMETERS_H

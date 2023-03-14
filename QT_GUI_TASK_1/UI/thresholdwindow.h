#ifndef THRESHOLDWINDOW_H
#define THRESHOLDWINDOW_H

#include <QDialog>

namespace Ui {
class ThresholdWindow;
}

class ThresholdWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdWindow(QWidget *parent = nullptr);
    ~ThresholdWindow();

    int ThresholdValue;
    bool flag;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ThresholdWindow *ui;
};

#endif // THRESHOLDWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gaussiannoiseparameters.h>
#include <saltpepperparameters.h>
#include <uniformnoiseparameters.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BrowseButton_clicked();

    void on_MedianFilterButton_clicked();

    void on_AverageFilterButton_clicked();

    void on_GrayScale_clicked();

    void on_GaussianFilterButton_clicked();

    void on_SaltPepperNoiseButton_clicked();

    void on_GaussianNoiseButton_clicked();

    bool checkImage();

    void on_UniformNoiseButton_clicked();

    void on_PrewittButton_clicked();

    void on_RobetButton_clicked();

    void on_SobelButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

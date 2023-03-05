#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_BrowseButton_clicked();

    void on_AddNoise_activated(int index);

    void on_AddNoise_currentIndexChanged(int index);

    void on_RemoveNoise_activated(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

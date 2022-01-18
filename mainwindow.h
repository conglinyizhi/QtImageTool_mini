#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>
#include "showimagewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void captureImage();
    void displayImage(int,QImage);
    void saveImage();
    void OpenImage();

signals:
    void sendImage(QImage,int,int);


private:
    Ui::MainWindow *ui;

    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    ShowImageWindow *showImageWindow;

};
#endif // MAINWINDOW_H

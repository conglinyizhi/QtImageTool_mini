#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camera=new QCamera(this);
    viewfinder=new QCameraViewfinder(this);
    imageCapture=new QCameraImageCapture(camera);


//    viewfinder->setGeometry(frameGeometry());
//    viewfinder->setStyleSheet(QString("background:#6cf"));
//    ui->view->addWidget(viewfinder);
    camera->setViewfinder(ui->widget);
    camera->start();

    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));
    connect(ui->buttonCapture, SIGNAL(clicked()), this, SLOT(captureImage()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(ui->buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::captureImage()
{

imageCapture->capture();
}

void MainWindow::displayImage(int , QImage image)
{
    showImageWindow = new ShowImageWindow();
    showImageWindow->show();
    connect(this,SIGNAL(sendImage(QImage)),showImageWindow,SLOT(getImage(QImage)));
    emit sendImage(image);
    disconnect(this,SIGNAL(sendImage(QImage)),showImageWindow,SLOT(getImage(QImage)));
}

void MainWindow::saveImage()
{
//QString fileName=QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
//if(fileName.isEmpty()) {
// //ui->statusBar->showMessage(tr("save cancel"), 5000);
//return;
//}
//const QPixmap* pixmap=ui->ImageCapture->pixmap();
//if(pixmap) {
//pixmap->save(fileName);
// //ui->statusBar->showMessage(tr("save OK"), 5000);
//}
}


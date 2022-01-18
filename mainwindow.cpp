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
    connect(ui->openImage,SIGNAL(clicked()),this,SLOT(OpenImage()));
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
    connect(this,SIGNAL(sendImage(QImage,int,int)),showImageWindow,SLOT(getImage(QImage,int,int)));
    if(ui->ImageRadio_Negative->isChecked()){
        emit sendImage(image,1,0);
    }else if(ui->ImageRadio_gray->isChecked()){
        emit sendImage(image,2,0);
    }else if(ui->ImageRadio_test->isChecked()){
        emit sendImage(image,3,0);
    }else if(ui->ImageRadio_bit->isChecked()){
        emit sendImage(image,4,ui->value->value());
    }else{
        emit sendImage(image,0,0);
    }

    disconnect(this,SIGNAL(sendImage(QImage,int,int)),showImageWindow,SLOT(getImage(QImage,int,int)));
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

void MainWindow::OpenImage(){
    QString f = QFileDialog::getOpenFileName(this,"选择一个图像文件","","所有支持的图形文件(*.png *.jpg *.jpeg *.bmp)");
    if(!f.isEmpty()){
        QImage i;
        i.load(f);
        emit displayImage(0,i);
    }
}

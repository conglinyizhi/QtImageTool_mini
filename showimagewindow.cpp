#include "showimagewindow.h"
#include "ui_showimagewindow.h"
#include <QDebug>
ShowImageWindow::ShowImageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowImageWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(SendChange(QPoint)),this,SLOT(ChangeColorByBit(QPoint)));
}

void ShowImageWindow::mouseMoveEvent(QMouseEvent *){
    QPoint p = this->cursor().pos();
    qDebug()<<p.x()-geometry().x()<<p.y()-geometry().y();
    qDebug()<<img.pixelColor(p.x()-geometry().x(),p.y()-geometry().y()).rgb();
    emit SendChange(QPoint(p.x()-geometry().x(),p.y()-geometry().y()));
}

void ShowImageWindow::mousePressEvent(QMouseEvent *){
    QPoint p = this->cursor().pos();
    QColor c = img.pixelColor(p.x()-geometry().x(),p.y()-geometry().y());
    qDebug()<<"red:"<<c.red()<<"green:"<<c.green()<<"blue:"<<c.blue();
}

ShowImageWindow::~ShowImageWindow()
{
    delete ui;
}

void ShowImageWindow::getImage(QImage i,int ImageSign){
    img = i;
    switch(ImageSign){
        case 1:
            for(long int y = 0;y<img.height();y++){
                for(long int x = 0;x<img.width();x++){
                    QColor getColor = img.pixelColor(x,y);
                    QColor color(255 - getColor.red(),255 - getColor.green(),255 - getColor.blue());
                    img.setPixelColor(x,y,color);
                }
            }
        break;
        case 0:
        break;
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
    setGeometry(x(),y(),img.width(),img.height());
    ui->label->setGeometry(0,0,img.width(),img.height());
}

void ShowImageWindow::ChangeColorByBit(QPoint p){
    img.setPixel(p.x(),p.y(),0xff66ccff);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

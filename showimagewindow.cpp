#include "showimagewindow.h"
#include "ui_showimagewindow.h"

ShowImageWindow::ShowImageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowImageWindow)
{
    ui->setupUi(this);    
}

ShowImageWindow::~ShowImageWindow()
{
    delete ui;
}

void ShowImageWindow::getImage(QImage i){
    QImage c = i;
    c.setPixel(10,10,0x66ccff);
    for(int pixStart = 0;pixStart < 255;pixStart ++){
        c.setPixel(pixStart,pixStart,0x66ccff);
    }
    ui->label->setPixmap(QPixmap::fromImage(c));
    ui->label->setScaledContents(true);
}

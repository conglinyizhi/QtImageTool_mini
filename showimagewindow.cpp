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
    ui->label->setPixmap(QPixmap::fromImage(i));
    ui->label->setScaledContents(true);
}

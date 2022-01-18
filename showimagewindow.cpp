#include "showimagewindow.h"
#include <QDebug>
#include "ui_showimagewindow.h"
ShowImageWindow::ShowImageWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::ShowImageWindow) {
    ui->setupUi(this);
    connect(this, SIGNAL(SendChange(QPoint)), this,
            SLOT(ChangeColorByBit(QPoint)));
}

void ShowImageWindow::mouseMoveEvent(QMouseEvent*) {
    QPoint p = this->cursor().pos();
    qDebug() << p.x() - geometry().x() << p.y() - geometry().y();
    qDebug()
        << img.pixelColor(p.x() - geometry().x(), p.y() - geometry().y()).rgb();
    emit SendChange(QPoint(p.x() - geometry().x(), p.y() - geometry().y()));
}

void ShowImageWindow::mousePressEvent(QMouseEvent*) {
    QPoint p = this->cursor().pos();
    QColor c = img.pixelColor(p.x() - geometry().x(), p.y() - geometry().y());
    qDebug() << "red:" << c.red() << "green:" << c.green()
             << "blue:" << c.blue();
}

ShowImageWindow::~ShowImageWindow() {
    delete ui;
}
double ShowImageWindow::ImageKerCalculator(QImage t_img,
                                           long int x,
                                           long int y,
                                           int w) {
    QColor c = t_img.pixelColor(x, y);
    return (c.red() + 0.59 * c.green() + 0.11 * c.blue()) / 3 * w;
}

void ShowImageWindow::getImage(QImage image, int ImageSign) {
    img = image;
    if (ImageSign == 1) {  // 负片
        for (long int y = 0; y < img.height(); y++) {
            for (long int x = 0; x < img.width(); x++) {
                QColor getColor = img.pixelColor(x, y);
                QColor color(255 - getColor.red(), 255 - getColor.green(),
                             255 - getColor.blue());
                img.setPixelColor(x, y, color);
            }
        }
    } else if (ImageSign == 2) {  // 灰度
        for (long int y = 0; y < img.height(); y++) {
            for (long int x = 0; x < img.width(); x++) {
                QColor getColor = img.pixelColor(x, y);
                long int tmp = getColor.red() + 0.59 * getColor.green() +
                               0.11 * getColor.blue();
                double t = tmp / 3;
                QColor color(t, t, t);
                img.setPixelColor(x, y, color);
            }
        }
    } else if (ImageSign == 3) {  // 3x3 卷积
        img = image;
        QImage copyImage = img.copy(0, 0, img.width(), img.height());
        for (long int y = 0; y < img.height(); y++) {
            for (long int x = 0; x < img.width(); x++) {
                if (x == 0 || y == 0 || x == img.width() || y == img.height()) {
                    int black = 0;
                    img.setPixelColor(x, y, black);
                } else {
                    double ker_1 =
                        ImageKerCalculator(copyImage, x - 1, y - 1, 0);
                    double ker_2 =
                        ImageKerCalculator(copyImage, x - 0, y - 1, -1);
                    double ker_3 =
                        ImageKerCalculator(copyImage, x + 1, y - 1, 0);
                    double ker_4 =
                        ImageKerCalculator(copyImage, x - 1, y - 0, -1);
                    double ker_5 =
                        ImageKerCalculator(copyImage, x - 0, y - 0, 5);
                    double ker_6 =
                        ImageKerCalculator(copyImage, x + 1, y - 0, -1);
                    double ker_7 =
                        ImageKerCalculator(copyImage, x - 1, y + 1, 0);
                    double ker_8 =
                        ImageKerCalculator(copyImage, x - 0, y + 1, -1);
                    double ker_9 =
                        ImageKerCalculator(copyImage, x + 1, y + 1, 0);
                    double t = ker_1 + ker_2 + ker_3 + ker_4 + ker_5 + ker_6 +
                               ker_7 + ker_8 + ker_9;
                    QColor color(t, t, t);
                    img.setPixelColor(x, y, color);
                }
            }
        }
    } else if (ImageSign == 4) {  // 二值
        for (long int y = 0; y < img.height(); y++) {
            for (long int x = 0; x < img.width(); x++) {
                QColor getColor = img.pixelColor(x, y);
                long int tmp = getColor.red() + 0.59 * getColor.green() +
                               0.11 * getColor.blue();
                double t = ((tmp / 3) > (128)) ? 255 : 0;
                QColor color(t, t, t);
                img.setPixelColor(x, y, color);
            }
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
    setGeometry(x(), y(), img.width(), img.height());
    ui->label->setGeometry(0, 0, img.width(), img.height());
}

void ShowImageWindow::ChangeColorByBit(QPoint p) {
    img.setPixel(p.x(), p.y(), 0xff66ccff);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

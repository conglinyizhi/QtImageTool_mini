#ifndef SHOWIMAGEWINDOW_H
#define SHOWIMAGEWINDOW_H

#include <QWidget>
#include <QImage>

namespace Ui {
class ShowImageWindow;
}

class ShowImageWindow : public QWidget
{
    Q_OBJECT

public slots:
    void getImage(QImage);

public:
    explicit ShowImageWindow(QWidget *parent = nullptr);
    ~ShowImageWindow();

private:
    Ui::ShowImageWindow *ui;
    QImage *img;
};

#endif // SHOWIMAGEWINDOW_H

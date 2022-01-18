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
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
public slots:
    void getImage(QImage,int);
    void ChangeColorByBit(QPoint);

signals:
    void SendChange(QPoint);

public:
    explicit ShowImageWindow(QWidget *parent = nullptr);
    ~ShowImageWindow();

private:
    Ui::ShowImageWindow *ui;
    QImage img;
};

#endif // SHOWIMAGEWINDOW_H

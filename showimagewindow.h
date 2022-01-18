#ifndef SHOWIMAGEWINDOW_H
#define SHOWIMAGEWINDOW_H

#include <QWidget>

namespace Ui {
class ShowImageWindow;
}

class ShowImageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShowImageWindow(QWidget *parent = nullptr);
    ~ShowImageWindow();

private:
    Ui::ShowImageWindow *ui;
};

#endif // SHOWIMAGEWINDOW_H

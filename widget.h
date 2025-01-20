#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "interface.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    interface *in;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

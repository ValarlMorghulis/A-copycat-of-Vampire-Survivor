#ifndef OVER_H
#define OVER_H

#include <QWidget>
#include"public.h"

namespace Ui {
class over;
}

class over : public QWidget
{
    Q_OBJECT

public:
    explicit over(QWidget *parent = nullptr);
    ~over();

signals:
    void Over();

private slots:
    void on_confirm_clicked();

private:
    Ui::over *ui;
};

#endif // OVER_H

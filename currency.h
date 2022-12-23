#ifndef CURRENCY_H
#define CURRENCY_H

#include <QWidget>
#include <QLabel>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>

namespace Ui {
class Currency;
}


class Currency : public QWidget
{
    Q_OBJECT
public:
    explicit Currency(QWidget *parent = nullptr);
    ~Currency();
private:
    Ui::Currency *ui;

};

#endif // CURRENCY_H

#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QWidget>
#include <QWidget>
#include<QStack>
#include <QKeyEvent>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include<QLabel>
#include<QLineEdit>
#include <math.h>


namespace Ui {
class Programmer;
}

class Programmer : public QWidget
{
    Q_OBJECT

public:
    explicit Programmer(QWidget *parent = nullptr);
    ~Programmer();



private:
    Ui::Programmer *ui;
};

#endif // PROGRAMMER_H

#ifndef STANDARD_H
#define STANDARD_H

#include <QWidget>
#include<QStack>
#include <QKeyEvent>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>


namespace Ui {
class Standard;
}

class Standard : public QWidget
{
    Q_OBJECT

public:
    explicit Standard(QWidget *parent = nullptr);
    ~Standard();


private:
    Ui::Standard *ui;
};

#endif // STANDARD_H

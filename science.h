#ifndef SCIENCE_H
#define SCIENCE_H

#include <QWidget>
#include <QWidget>
#include<QStack>
#include <QKeyEvent>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>

namespace Ui {
class Science;
}

class Science : public QWidget
{
    Q_OBJECT

public:
    explicit Science(QWidget *parent = nullptr);
    ~Science();


private:
    Ui::Science *ui;
};

#endif // SCIENCE_H

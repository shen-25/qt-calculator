﻿#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <QLabel>
#include<QMap>
#include<QPushButton>
#include<QDebug>
#include <math.h>

namespace Ui {
class Volume;
}



class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();

private:
    Ui::Volume *ui;


};

#endif // VOLUME_H

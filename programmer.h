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
    bool  eventFilter(QObject *obj, QEvent *event);

    int curRow ;
    int curJZ;
    int lastJZ;
    QLabel *displayJZ;

    QString operand;
    QString op;
    QString lastKey;
    QVector<QString> operands;
    QVector<QPushButton *> digitBTNs;
    QVector<QLabel *>  labels;

    QString calculation( );

private slots:


    void  updateDisplayJZ(int row);

    void on_btnEqual_clicked();

    void on_btnClearAll_clicked();

    void on_btnZhengFu_clicked();
    void on_btnPeriod_clicked();

    void on_btnDel_clicked();



    void btnNumClicked();

    void transJZ();

    void btnBinaryOperatorClicked();

    void btnUnaryOperatorClicked();




    virtual void keyPressEvent(QKeyEvent *event);


private:
    Ui::Programmer *ui;
};

#endif

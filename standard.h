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

    QString operand;
    QString op;
    QString lastKey;
    QStack<QString> operands;
    QMap<int,QPushButton *> digitBTNs;

    QString calculation( );

private slots:

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();

    void on_btnClear_clicked();

    void on_btnEqual_clicked();

    void on_btnClearAll_clicked();

    void on_btnZhengFu_clicked();

    void btnNumClicked();

    void btnBinaryOperatorClicked();

    void btnUnaryOperatorClicked();




    virtual void keyPressEvent(QKeyEvent *event);
private:
    Ui::Standard *ui;
};

#endif // STANDARD_H

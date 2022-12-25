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
    QString operand;
    QString op;
    QString lastKey;
    QStack<QString> operands;
    QMap<int,QPushButton *> digitBTNs;

    QString calculation( );

private slots:
    void btnNumClicked();

    void on_btnPeriod_clicked();

    void on_btnDel_clicked();


    void btnBinaryOperatorClicked();

    void on_btnClear_clicked();

    void btnUnaryOperatorClicked();
    void on_btnEqual_clicked();

    void on_btnClearAll_clicked();

    void on_btnZhengFu_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Science *ui;
};

#endif

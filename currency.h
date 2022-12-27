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

enum CurrencyType
{
    CHN=1,
    USA=2
};

class Currency : public QWidget
{
    Q_OBJECT

public:
    explicit Currency(QWidget *parent = nullptr);
    ~Currency();
     bool eventFilter(QObject *obj, QEvent *event);
     void UpdateCur(QLabel*  lbl);
     QMap<int,QPushButton *> digitBTNs;
    void tranCurrency();
private slots:
    void on_btnPeriod_clicked();
    void on_btnDel_clicked();

    void btnNumClicked();

    void on_btnClearAll_clicked();

private:
    Ui::Currency *ui;
     CurrencyType  curType;
     QLabel * display;
     QString operand;
};

#endif // CURRENCY_H

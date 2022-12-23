#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "ICalculator.h"

// QCalculatorUI间接继承QObject
class QCalculatorUI : public QWidget
{
    // 自定义类起始处添加Q_OBJECT
    Q_OBJECT;

private:
    QLineEdit* m_edit;
    QPushButton* m_buttons[20];

    // 计算逻辑类 => 把从UI类获取的"运算表达式"传入逻辑类进行计算
    ICalculator* m_cal;

    // 二阶构造模式
    QCalculatorUI();
    bool construct();

    // 关联函数
private slots:
    void onButtonClicked();

public:
    static QCalculatorUI* NewInstance();

    // set/get函数
    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();

    void show();

    ~QCalculatorUI();
};

#endif  // QCALCULATORUI_H

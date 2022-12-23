#ifndef QCALCULATOR_H
#define QCALCULATOR_H

#include "QCalculatorDec.h"
#include "QCalculatorUI.h"

class QCalculator
{
private:
    // 局部逻辑变量
    QCalculatorDec m_dec;
    // 局部UI变量, 指向堆内存空间, 注意最后要进行释放
    QCalculatorUI* m_ui;

    QCalculator();
    bool construct();

public:
    // 使用二阶构造模式
    static QCalculator* NewInstance();

    void show();

    ~QCalculator();
};

#endif  // QCALCULATOR_H

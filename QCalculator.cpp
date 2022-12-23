#include "QCalculator.h"

QCalculator::QCalculator() {}

bool QCalculator::construct()
{
    bool ret = false;

    // 调用UI类的二阶构造函数
    m_ui = QCalculatorUI::NewInstance();

    if(m_ui != NULL)
    {
        // 将UI类与逻辑类进行关联
        m_ui->setCalculator(&m_dec);
        ret = true;
    }

    return ret;
}

QCalculator* QCalculator::NewInstance()
{
    QCalculator* ret = new QCalculator();

    // 任意对象创建失败时, 释放指针, 并赋空
    if((ret == NULL) || (!ret->construct()))
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void QCalculator::show()
{
    // 调用UI类的show函数
    m_ui->show();
}

QCalculator::~QCalculator()
{
    // 释放UI指针所指向的堆内存空间
    delete m_ui;
}

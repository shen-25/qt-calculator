#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H

#include <QDebug>
#include <QQueue>
#include <QStack>
#include <QString>

#include "ICalculator.h"

class QCalculatorDec : public ICalculator
{
protected:
    QString m_exp;
    QString m_result;

    bool isDigitOrDot(QString s);
    bool isSymbol(QString s);
    bool isNumber(QString s);
    bool isSign(QString s);
    bool isOperator(QString s);
    bool isLeftBracket(QString s);
    bool isRightBracket(QString s);

    int priority(QString s);
    bool mathBracket(QQueue< QString >& exp);
    QQueue< QString > split(const QString& exp);
    bool transform(QQueue< QString >& exp, QQueue< QString >& out);
    QString calculate(QString ls, QString op, QString rs);
    QString calculate(QQueue< QString >& exp);

public:
    QCalculatorDec();

    bool expression(const QString& exp);
    QString expression();
    QString result();

    ~QCalculatorDec();
};

#endif  // QCALCULATORDEC_H

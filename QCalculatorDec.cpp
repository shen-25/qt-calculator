#include "QCalculatorDec.h"

// 数字或小数点判断函数
bool QCalculatorDec::isDigitOrDot(QString s)
{
    return (isNumber(s) || (s == "."));
}

// 符号判断函数
bool QCalculatorDec::isSymbol(QString s)
{
    return (isOperator(s) || isLeftBracket(s) || isRightBracket(s));
}

// 数字判断函数
bool QCalculatorDec::isNumber(QString s)
{
    bool ret = false;

    s.toDouble(&ret);

    return ret;
}

// 符号位判断函数
bool QCalculatorDec::isSign(QString s)
{
    return ((s == "+") || (s == "-"));
}

// 操作符判断函数
bool QCalculatorDec::isOperator(QString s)
{
    return (isSign(s) || s == "*" || s == "/");
}

// 左括号判断函数
bool QCalculatorDec::isLeftBracket(QString s)
{
    return (s == "(");
}

// 右括号判断函数
bool QCalculatorDec::isRightBracket(QString s)
{
    return (s == ")");
}

// 运算优先级判断函数
int QCalculatorDec::priority(QString s)
{
    int ret = 0;

    if(isSign(s))
    {
        // +或-时, 优先级为1
        ret = 1;
    }
    else if(s == "*" || s == "/")
    {
        // *或/时, 优先级为2(1 < 2)
        ret = 2;
    }
    else
    {
        // TODO...
    }

    return ret;
}

// 左右括号匹配函数
bool QCalculatorDec::mathBracket(QQueue< QString >& exp)
{
    bool ret = true;

    int len = exp.length();

    if(len > 0)
    {
        QStack< QString > stack;

        for(int i = 0; i < len; i++)
        {
            QString s = exp[i];

            // 符号为左括号时, 入栈
            if(isLeftBracket(s))
            {
                stack.push(s);
                ret = false;
            }
            // 符号为右括号时, 出栈
            else if(isRightBracket(s))
            {
                if(!stack.isEmpty() && isLeftBracket(stack.top()))
                {
                    stack.pop();
                    ret = true;
                }
                else
                {
                    // 符号为右括号, 但栈内为空时, 则括号匹配失败, 且循环直接结束
                    ret = false;
                    break;
                }
            }
            else
            {
                // TODO...
            }
        }

        // 最后左右符号正好匹配, 此时栈理应为空, 且不是右括号匹配失败而导致的循环匹配结束
        ret = ret && stack.isEmpty();
    }
    else
    {
        // TODO...
    }

    return ret;
}

// 分离算法, 将运算表达式进行分离
QQueue< QString > QCalculatorDec::split(const QString& exp)
{
    QQueue< QString > ret;

    QString pre = "";
    QString number = "";

    int len = exp.length();

    for(int i = 0; i < len; i++)
    {
        QString s = exp[i];

        // 判断是否为数字(数字或者小数点)
        if(isDigitOrDot(s))
        {
            number += s;
        }
        // 判断是否为符号(符号位, 运算符, 括号)
        else if(isSymbol(s))
        {
            // 将得到的数字加入返回队列, 因为该符号已不可能为数字一部分
            if(!number.isEmpty())
            {
                ret.enqueue(number);

                // 清空数字, 为保存下一数字作准备
                number.clear();
            }

            // 判断是否为符号位(当前为正负号, 且前一位为: 空 左括号 运算符)
            if(isSign(s) && (pre == "" || isLeftBracket(pre) || isOperator(pre)))
            {
                number = s;
            }
            else
            {
                // 将非符号位符号加入返回队列
                ret.enqueue(s);
            }
        }
        else
        {
            // TODO...
        }

        if(s != " ")
        {
            // 更新前一字符
            pre = s;
        }
    }

    // 将最后的数字, 加入返回队列
    if(!number.isEmpty())
    {
        ret.enqueue(number);
    }

    return ret;
}

// 中缀转后缀函数的实现 => 计算机程序逻辑更能对后缀表达式进行识别与计算
bool QCalculatorDec::transform(QQueue< QString >& exp, QQueue< QString >& out)
{
    bool ret = mathBracket(exp);

    QStack< QString > stack;
    out.clear();

    while(ret && !exp.isEmpty())
    {
        // dequeue: 删除头部并返回
        QString s = exp.dequeue();

        if(isNumber(s))
        {
            // 将数字加入返回队列
            out.enqueue(s);
        }
        else if(isOperator(s))
        {
            // 将优先度更高的操作符出栈, 并加入到返回队列
            while(!stack.isEmpty() && priority(s) < priority(stack.top()))
            {
                out.enqueue(stack.pop());
            }

            // 将此次操作符入栈
            stack.push(s);
        }
        else if(isLeftBracket(s))
        {
            // 将左括号入栈
            stack.push(s);
        }
        else if(isRightBracket(s))
        {
            // 将栈中操作符与右括号进行匹配, 直至找到左括号前, 并将左括号前的操作符加入到返回队列
            while(!stack.isEmpty() && !isLeftBracket(stack.top()))
            {
                out.enqueue(stack.pop());
            }

            if(!stack.isEmpty())
            {
                // 将栈中左括号出栈
                stack.pop();
            }
            else
            {
                // 左括号未出栈, 栈不应为空, 为空则失败
                ret = false;
            }
        }
        else
        {
            // TODO...
        }
    }

    // 将栈中剩余的操作符进行加入到返回队列
    while(!stack.isEmpty())
    {
        out.enqueue(stack.pop());
    }

    // 判断转换过程是否成功, 失败则清空返回队列
    if(!ret)
    {
        out.clear();
    }

    return ret;
}

// 计算子函数
QString QCalculatorDec::calculate(QString ls, QString op, QString rs)
{
    QString ret = "Error";

    if(isNumber(ls) && isNumber(rs))
    {
        double ld = ls.toDouble();
        double rd = rs.toDouble();

        if(op == "+")
        {
            // 加法的情况
            ret.sprintf("%f", ld + rd);
            // ret = QString("%f").arg(ld + rd);
        }
        else if(op == "-")
        {
            // 减法的情况
            ret.sprintf("%f", ld - rd);
            // ret = QString("%f").arg(ld - rd);
        }
        else if(op == "*")
        {
            // 乘法的情况
            ret.sprintf("%f", ld * rd);
            // ret = QString("%f").arg(ld * rd);
        }
        else if(op == "/")
        {
            // 除法的情况, 需进行除数为否为零的判断
            const double d = 0.000000000000001;

            if((-d < rd) && (rd < d))
            {
                // 除数为零, 返回异常
                ret = "Error";
            }
            else
            {
                // 除数不为零, 运算正常进行
                ret.sprintf("%f", ld / rd);
                // ret = QString("%f").arg(ld / rd);
            }
        }
        else
        {
            // 运算符异常
            ret = "Error";
        }
    }

    return ret;
}
// 计算函数
QString QCalculatorDec::calculate(QQueue< QString >& exp)
{
    QString ret = "Error";
    QStack< QString > stack;

    while(!exp.isEmpty())
    {
        QString s = exp.dequeue();

        if(isNumber(s))
        {
            stack.push(s);
        }
        else if(isOperator(s))
        {
            // 获取操作数
            QString rs = !stack.isEmpty() ? stack.pop() : "";
            QString ls = !stack.isEmpty() ? stack.pop() : "";

            // 计算子函数
            QString result = calculate(ls, s, rs);

            if(result != "Error")
            {
                stack.push(result);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    // 运算结束, 对结果进行判断 => 四则运算表达式为空, 栈中保存数字结果
    if(exp.isEmpty() && (stack.length() == 1) && isNumber(stack.top()))
    {
        ret = stack.top();
    }

    return ret;
}

// 无参构造函数
QCalculatorDec::QCalculatorDec()
{
    m_exp = "";
    m_result = "";
}

// 计算函数 => 外部调用
bool QCalculatorDec::expression(const QString& exp)
{
    bool ret = false;
    m_exp = exp;

    // 分离四则运算表达式
    QQueue< QString > splitStr = split(exp);

    // 中缀转后缀
    QQueue< QString > transStr;
    ret = transform(splitStr, transStr);

    if(ret)
    {
        // 计算结果
        m_result = calculate(transStr);

        // 对计算结果进行判断
        ret = (m_result != "Error");
    }

    return ret;
}

QString QCalculatorDec::result()
{
    return m_result;
}

QCalculatorDec::~QCalculatorDec() {}

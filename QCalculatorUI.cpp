#include "QCalculatorUI.h"

// 构造函数
QCalculatorUI::QCalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint) {}

// 构造函数
bool QCalculatorUI::construct()
{
    bool ret = false;
    const char* btnText[20] = { "7", "8", "9", "+", "(", "4", "5", "6", "-", ")", "1", "2", "3", "*", "<-", "0", ".", "=", "/", "C" };

    m_edit = new QLineEdit(this);

    if(m_edit != NULL)
    {
        // 输出框: 大小, 基于窗口的偏移量
        m_edit->resize(240, 30);
        m_edit->move(10, 10);

        // 属性: 只读, 向右对齐
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);

        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                m_buttons[i * 5 + j] = new QPushButton(this);

                if(m_buttons[i * 5 + j] != NULL)
                {
                    // 按钮大小, 基于窗口的偏移量
                    m_buttons[i * 5 + j]->resize(40, 40);
                    m_buttons[i * 5 + j]->move(10 + (10 + 40) * j, 50 + (10 + 40) * i);

                    // 按钮文本
                    m_buttons[i * 5 + j]->setText(btnText[i * 5 + j]);

                    // 按钮点击事件绑定关联函数
                    connect(m_buttons[i * 5 + j], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
                }
            }
        }

        ret = true;
    }

    return ret;
}

// 实现点击按钮的关联函数
void QCalculatorUI::onButtonClicked()
{
    QPushButton* btn = dynamic_cast< QPushButton* >(sender());

    QString editText = m_edit->text();
    QString btnText = btn->text();

    qDebug() << "onButtonClicked: " << editText + btnText;

    if(btnText == "C")
    {
        m_edit->setText("");
    }
    else if(btnText == "<-")
    {
        int len = editText.length();

        if(len > 0)
        {
            m_edit->setText(editText.remove(len - 1, 1));
        }
    }
    else if(btnText == "=")
    {
        if(m_cal != NULL)
        {
            // 将四则运算表达式传入逻辑类进行计算
            m_cal->expression(editText);

            // 获取逻辑类的计算结果, 并将其显示
            m_edit->setText(m_cal->result());
        }
    }
    else
    {
        m_edit->setText(editText + btnText);
    }
}

// 实例函数
QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI* ret = new QCalculatorUI();

    if((ret == NULL) || (!ret->construct()))
    {
        delete ret;

        ret = NULL;
    }

    return ret;
}

void QCalculatorUI::show()
{
    QWidget::show();

    move(1200, 300);
    setFixedSize(frameGeometry().width(), frameGeometry().height());

    qDebug() << "x=" << x() << "y=" << y() << "width=" << width() << "height=" << height();
    qDebug() << "geometry.x=" << geometry().x() << "geometry.y=" << geometry().y() << "geometry.width=" << geometry().width() << "geometry.height=" << geometry().height();
    qDebug() << "frameGeometry.x=" << frameGeometry().x() << "frameGeometry.y=" << frameGeometry().y() << "frameGeometry.width=" << frameGeometry().width()
             << "frameGeometry.height=" << frameGeometry().height();
}

// set/get函数
void QCalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}
ICalculator* QCalculatorUI::getCalculator()
{
    return m_cal;
}

// 析构函数
QCalculatorUI::~QCalculatorUI()
{
    delete m_edit;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            delete m_buttons[i * 5 + j];
        }
    }
}

#include "standard.h"
#include "ui_standard.h"

Standard::Standard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Standard)
{
    ui->setupUi(this);


    digitBTNs = {{Qt::Key_0,ui->btnNum0},
               {Qt::Key_1,ui->btnNum1}, {Qt::Key_2,ui->btnNum2},
               {Qt::Key_3,ui->btnNum3},      {Qt::Key_4,ui->btnNum4},
               {Qt::Key_5,ui->btnNum5},
               {Qt::Key_6,ui->btnNum6},
               {Qt::Key_7,ui->btnNum7},     {Qt::Key_8,ui->btnNum8},
               {Qt::Key_9,ui->btnNum9},
              };
    foreach(auto btn, digitBTNs)
         connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
}

QString  Standard::calculation( )
{
        double result =0;


        double operand1 = operands.pop().toDouble();
        double operand2 = operands.pop().toDouble();

        if(op == "+"){
            result = operand1 + operand2;
        }
        else if(op == "-"){
            result = operand1 - operand2;
        }
        else if(op == "×"){
            result = operand1 * operand2;
        }
        else if(op == "÷"){
            result = operand1 / operand2;
        }

      return QString::number(result);

}


void Standard::btnNumClicked()
{

    if(       lastKey == "="     || lastKey =="1/x"
           || lastKey =="%"     || lastKey =="2√x"  || lastKey =="x²"  )
    {
        on_btnClearAll_clicked();
    }


    QString digit = qobject_cast<QPushButton*>(sender())->text();
    lastKey = digit;

    if(operand == "0" )
    {
        operand =digit;
    }
   else
    {
         operand +=digit;
    }


    ui->display->setText(operand);
}



void Standard::on_btnPeriod_clicked()
{

    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);
}


void Standard::on_btnDel_clicked()
{


    if( operand.length()>0 )
    {
         operand =operand.left(operand.length()-1);
         ui->display->setText(operand);
    }

}


void Standard::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);

}

void Standard::on_btnClearAll_clicked()
{
    operand.clear();
    operands.clear();
    op="";
    lastKey="";
    ui->display->setText(operand);
}


void Standard::btnBinaryOperatorClicked()
{
    if( operand.length()>0)
    {
       operands.push_front(operand);
    }

    if(op!=""  &&  operands.size()==2 )
    {
          QString   ret = calculation();
          ui->display->setText(   ret  );

          operands.push_front(ret);
    }

    operand ="";
    op = qobject_cast<QPushButton *>(sender())->text();
    lastKey = op;
}


void Standard::btnUnaryOperatorClicked()
{
    if(operand != "")
    {
        double result = operand.toDouble();

         QString   uo = qobject_cast<QPushButton*>(sender())->text();
         lastKey = uo;

        if(uo == "%")
            result /=100.0;
        else if(uo =="1/x")
            result =1/result;
        else if(uo =="x²")
            result *=result;
        else if(uo =="2√x")
            result = sqrt(result);

        ui->display->setText(QString::number(result));

        operand  = QString::number( result );
    }
}


void Standard::on_btnEqual_clicked()
{
    QString   eq = qobject_cast<QPushButton*>(sender())->text();
    lastKey = eq;

    if( operand.length()>0){
       operands.push_front(operand);
    }

    if(op!=""  &&  operands.size()==2 ) {
          QString   ret = calculation();
          operand = ret;

          ui->display->setText(   operand  );
          operands.push_front(operand);
    }

}


void Standard::on_btnZhengFu_clicked(){
    QString   zf = qobject_cast<QPushButton*>(sender())->text();
    lastKey = zf;

    if( operand .length()>0){
        if(operand.left(1)=="-")  {
            operand=operand.right(operand.length()-1);
        }
        else{
            operand="-"+operand;
        }
        ui->display->setText(operand);
    }


}

//按键事件操作符的逻辑处理
void Standard::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();

        foreach(auto btnkey , digitBTNs.keys()) {
            if(event->key() == btnkey)
                digitBTNs[btnkey]->animateClick(100);
        }

        if(event->text() == "+" ){
            ui->btnPlus->animateClick(100);
        }
        else if(event->text() == "-" ){
            ui->btnMinus->animateClick(100);
        }
        else if(event->text() == "×" ){
           ui->btnMultiple->animateClick(100);
        }
        else if(event->text() == "÷" ){
          ui->btnDivide->animateClick(100);
        }
        else if(event->text() == "." ){
          ui->btnPeriod->animateClick(100);
        }
        else if(event->text() == "%" ){
            ui->btnPercentage->animateClick(100);
        }
        else if(event->text() == "=" ){
         ui->btnEqual->animateClick(100);
        }
        else if(event->key() == Qt::Key_Backspace ){
            ui->btnDel->animateClick(100);
        }
}

Standard::~Standard()
{
    delete ui;
}

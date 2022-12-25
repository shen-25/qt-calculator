#include "science.h"
#include "ui_science.h"

Science::Science(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Science)
{
    ui->setupUi(this);


    digitBTNs = {{Qt::Key_0,ui->btnNum0},
               {Qt::Key_1,ui->btnNum1},
               {Qt::Key_2,ui->btnNum2},
               {Qt::Key_3,ui->btnNum3},
               {Qt::Key_4,ui->btnNum4},
               {Qt::Key_5,ui->btnNum5},
               {Qt::Key_6,ui->btnNum6},
               {Qt::Key_7,ui->btnNum7},
               {Qt::Key_8,ui->btnNum8},
               {Qt::Key_9,ui->btnNum9},
              };
    foreach(auto btn, digitBTNs)
         connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));



    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnXy,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));


     connect(ui->btnLn,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnLog,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btn10x,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnN1,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnE,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnPI,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnAbs,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
     connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}



QString  Science::calculation( )
{
        double res =0;


        double operand1 = operands.pop().toDouble();
        double operand2 = operands.pop().toDouble();

        if(op == "+"){
            res = operand1 + operand2;
        }
        else if(op == "-"){
            res = operand1 - operand2;
        }
        else if(op == "×"){
            res = operand1 * operand2;
        }
        else if(op == "÷"){
            res = operand1 / operand2;
        }
        else if(op == "x^y"){
            res = pow( operand1  ,operand2);
        }
      return QString::number(res);

}







void Science::on_btnDel_clicked(){
    if( operand.length()>0 ){
         operand =operand.left(operand.length()-1);
         ui->display->setText(operand);
    }
}

void Science::btnNumClicked()
{
    if(       lastKey == "="     || lastKey =="1/x"
              || lastKey =="log" || lastKey =="|x|"
           || lastKey =="%"     || lastKey =="2√x"
              || lastKey =="x²"   || lastKey =="ln"
           || lastKey =="10^x"|| lastKey =="n!")
    {
        on_btnClearAll_clicked();
    }

    QString digit = qobject_cast<QPushButton*>(sender())->text();
    lastKey = digit;

    if(operand == "0" ) {
        operand =digit;
    }
   else{
         operand +=digit;
    }


    ui->display->setText(operand);
}

void Science::on_btnPeriod_clicked(){

    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);
}


void Science::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);

}

void Science::on_btnClearAll_clicked()
{
    operand.clear();
    operands.clear();
    op="";
    lastKey="";
    ui->display->setText(operand);
}

int  fact(int ip) {
    if (ip == 1) {
        return 1;
    }
    else {
        return ip * fact(ip - 1);
    }
}


void Science::btnUnaryOperatorClicked()
{
    QString   uo = qobject_cast<QPushButton*>(sender())->text();
    lastKey = uo;

   if(uo =="π")
   {
       operand  = "3.1415926535897932384626433832795";
       ui->display->setText( operand );
       ui->display->setCursorPosition(0);
   }
   else if(uo =="e")
   {
       operand  = "2.7182818284590452353602874713527";
       ui->display->setText( operand );
       ui->display->setCursorPosition(0);
   }
   else
   {
       if(operand != "")
       {
            double res = operand.toDouble();

           if(uo == "%")
               res /=100.0;
           else if(uo =="1/x")
               res =1/res;
           else if(uo =="x²")
               res *=res;
           else if(uo =="2√x")
               res = sqrt(res);
           else if(uo =="|x|")
               res = abs(res);
           else if(uo =="n!")
               res = fact(res);
           else if(uo =="10^x")
               res = pow(10, res);
           else if(uo =="log")
               res = log10(  res);
           else if(uo =="ln")
               res = log( res);
           operand  = QString::number( res );
           ui->display->setText( operand );
       }
   }


}

void Science::btnBinaryOperatorClicked()
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





void Science::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();


    foreach(auto btnkey , digitBTNs.keys())
    {
        if(event->key() == btnkey)
            digitBTNs[btnkey]->animateClick(100);
    }

    if(event->text() == "+" )
            ui->btnPlus->animateClick(100);
        else if(event->text() == "-" )
            ui->btnMinus->animateClick(100);
        else if(event->text() == "×" )
            ui->btnMultiple->animateClick(100);
        else if(event->text() == "÷" )
            ui->btnDivide->animateClick(100);
        else if(event->text() == "." )
            ui->btnPeriod->animateClick(100);
        else if(event->text() == "=" )
            ui->btnEqual->animateClick(100);
        else if(event->key() == Qt::Key_Backspace )
            ui->btnDel->animateClick(100);

}

void Science::on_btnEqual_clicked()
{
    QString   eq = qobject_cast<QPushButton*>(sender())->text();
    lastKey = eq;

    if( operand.length()>0)
    {
       operands.push_front(operand);
    }

    if(op!=""  &&  operands.size()==2 )
    {
          QString   ret = calculation();
          operand = ret;

          ui->display->setText(   operand  );
          operands.push_front(operand);
    }

}

void Science::on_btnZhengFu_clicked()
{
    QString   zf = qobject_cast<QPushButton*>(sender())->text();
    lastKey = zf;

    if( operand .length()>0)
    {
        if(operand.left(1)=="-")
        {
            operand=operand.right(operand.length()-1);
        }
        else
        {
            operand="-"+operand;
        }
        ui->display->setText(operand);
    }


}


Science::~Science()
{
    delete ui;
}


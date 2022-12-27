#include "currency.h"
#include "ui_currency.h"

Currency::Currency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Currency){
    ui->setupUi(this);

    ui->labelCHN->installEventFilter(this);

    ui->labelUSA->installEventFilter(this);


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

     UpdateCur(ui->labelCHN);

}



//添加小数点
void Currency::on_btnPeriod_clicked(){

    if(!operand.contains(".")){
        //添加新按的数字
        operand +=qobject_cast<QPushButton*>(sender())->text();
    }
    display->setText(operand);
}


void Currency::btnNumClicked(){

    QString digit = qobject_cast<QPushButton*>(sender())->text();

    if(operand == "0" ){
        operand =digit;
    }
   else {
         operand +=digit;
    }

   display->setText(operand);
   tranCurrency( );
}
//1美元等于6.9605元，汇率换算
static double K = 6.9605;

void Currency::tranCurrency( ){

    if( curType == CHN) {
        double chn = operand.toDouble();
        double usa = chn / K;
        ui->labelUSA->setText(QString("%1").arg(usa));
    }
    else if( curType == USA){
        double usa = operand.toDouble();
        double chn = usa * K;
        ui->labelCHN->setText(QString("%1").arg(chn));
    }


}

void Currency::UpdateCur(QLabel*  lbl){

    display = lbl;

    if(  display ==  ui->labelCHN ){
     curType = CHN;
    }

    else if(  display ==  ui->labelUSA ){
      curType = USA;
    }
    //第一个参数是字体（微软雅黑），第二个参数是大小，第三个参数是加粗（权重是75）
    QFont font1 ("Microsoft YaHei", 14, QFont::Normal);
    ui->labelCHN->setFont(font1);
    ui->labelUSA->setFont(font1);

    QFont font2 ("Microsoft YaHei", 18, QFont::Bold);
    display->setFont(font2);

    operand = display->text();
}


void Currency::on_btnDel_clicked(){

    if( operand.length()>0 )  {
         operand =operand.left(operand.length()-1);

    }

    if(operand.length()==0)  {
        operand= "0";
    }
    //把按键的数字显示出来
      display->setText(operand);
     tranCurrency( );
}


Currency::~Currency(){
    delete ui;
}

void Currency::on_btnClearAll_clicked(){
    ui->labelCHN->setText("0");
    ui->labelUSA->setText("0");
    operand ="0";
}
bool Currency::eventFilter(QObject *obj, QEvent *event){
    if( event->type() == QEvent::MouseButtonPress)  {
       display =(  QLabel *) obj;
        UpdateCur(display);

        return true;
    }

    return false;
}


#include "datecalc.h"
#include "ui_datecalc.h"

DateCalc::DateCalc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateCalc)
{
    ui->setupUi(this);

}


DateCalc::~DateCalc()
{
    delete ui;
}

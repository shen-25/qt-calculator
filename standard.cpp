#include "standard.h"
#include "ui_standard.h"

Standard::Standard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Standard)
{
    ui->setupUi(this);


}


Standard::~Standard()
{
    delete ui;
}

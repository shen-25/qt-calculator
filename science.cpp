#include "science.h"
#include "ui_science.h"

Science::Science(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Science)
{
    ui->setupUi(this);

}

Science::~Science()
{
    delete ui;
}


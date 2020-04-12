#include "twopointfunction.h"
#include "ui_twopointfunction.h"

TwoPointFunction::TwoPointFunction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointFunction)
{
    ui->setupUi(this);
}

TwoPointFunction::~TwoPointFunction()
{
    delete ui;
}

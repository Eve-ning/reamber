#include "stutter.h"
#include "ui_stutter.h"

Stutter::Stutter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stutter)
{
    ui->setupUi(this);
}

Stutter::~Stutter()
{
    delete ui;
}

#include "alter.h"
#include "ui_alter.h"

Alter::Alter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alter)
{
    ui->setupUi(this);
}

Alter::~Alter()
{
    delete ui;
}

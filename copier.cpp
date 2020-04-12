#include "copier.h"
#include "ui_copier.h"

Copier::Copier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Copier)
{
    ui->setupUi(this);
}

Copier::~Copier()
{
    delete ui;
}

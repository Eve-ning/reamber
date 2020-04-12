#include "twopointbezier.h"
#include "ui_twopointbezier.h"

TwoPointBezier::TwoPointBezier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointBezier)
{
    ui->setupUi(this);
}

TwoPointBezier::~TwoPointBezier()
{
    delete ui;
}

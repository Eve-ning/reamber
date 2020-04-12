#include "normalizer.h"
#include "ui_normalizer.h"

Normalizer::Normalizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Normalizer)
{
    ui->setupUi(this);
}

Normalizer::~Normalizer()
{
    delete ui;
}

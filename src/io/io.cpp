#include "include/io/io.h"
#include "ui_iowidget.h"
#include "object/multiple/timingpointv.h"
#include "object/multiple/hitobjectv.h"

IO::IO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOWidget) {
    ui->setupUi(this);
}

IO::~IO(){
    delete ui;
}

QString IO::toPlainText() const {
    return ui->text->toPlainText();
}

QLayout *IO::getLayout() const {
    return ui->gridLayout_2;
}

void IO::on_text_textChanged() {
    emit textChanged(toPlainText());
}

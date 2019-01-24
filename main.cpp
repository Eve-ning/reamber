#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <memory>
#include <QDebug>
#include <custom_lib_functions/lib_functions.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    timing_point tp;
    qDebug() << tp.get_string_raw().c_str();

//    w.show();

    return a.exec();

}

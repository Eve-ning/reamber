#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <memory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();

    return QApplication::exec();
}

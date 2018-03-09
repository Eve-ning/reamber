#include "amber.h"
#include "ui_amber.h"
#include <QApplication>
#include <QDialog>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    amber w;

    w.show();
    return a.exec();
}

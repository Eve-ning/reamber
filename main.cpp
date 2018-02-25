#include "amber.h"
#include "ui_amber.h"
#include "check.h"
#include "convert.h"
#include "defargs.h"
#include "compile.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    amber w;

    w.show();
    return a.exec();
}

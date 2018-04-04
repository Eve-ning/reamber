#include "amber.h"
#include "ui_amber.h"
#include <QApplication>
#include <QDialog>

#include "amber_base_inc.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    amber w;

    w.show();
    return a.exec();
}

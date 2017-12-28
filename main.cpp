#include "svTool.h"
#include "ui_svTool.h"
#include <QApplication>
#include <QDialog>
#include <QTabWidget>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    svTool w;
    w.show();
    return a.exec();
}

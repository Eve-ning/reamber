#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <memory>
#include <QPalette>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/rsc/amber.ico"));

    w.show();

    a.setStyle("Fusion");

    QFont font("Segoe Ui");
    QApplication::setFont(font);

    QColor darkFade = QColor(60, 60, 60);
    QColor dark = QColor(40, 40, 40);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window,          darkFade);
    palette.setColor(QPalette::WindowText,      Qt::white);
    palette.setColor(QPalette::Base,            dark);
    palette.setColor(QPalette::AlternateBase,   darkFade);
    palette.setColor(QPalette::ToolTipBase,     Qt::white);
    palette.setColor(QPalette::ToolTipText,     Qt::white);
    palette.setColor(QPalette::Text,            Qt::white);
    palette.setColor(QPalette::Button,          darkFade);
    palette.setColor(QPalette::ButtonText,      Qt::white);
    palette.setColor(QPalette::BrightText,      Qt::red);
    palette.setColor(QPalette::Link,            QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight,       QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::black);
    a.setPalette(palette);

    return QApplication::exec();
}

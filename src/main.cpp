#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <memory>
#include <QPalette>
#include <QFile>

void setUITheme(QApplication & a);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/rsc/amber.ico"));
    setUITheme(a);
    w.show();

    return QApplication::exec();
}


void setUITheme(QApplication & a) {

    // Make UI consistent across systems
    a.setStyle("Fusion");

    // Set font
    QFont font("Segoe Ui");
    QApplication::setFont(font);

    // Sets the dark theme
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window,          QColor(60, 60, 60));
    palette.setColor(QPalette::WindowText,      Qt::white);
    palette.setColor(QPalette::Base,            QColor(40, 40, 40));
    palette.setColor(QPalette::AlternateBase,   QColor(60, 60, 60));
    palette.setColor(QPalette::Text,            Qt::white);
    palette.setColor(QPalette::Button,          QColor(60, 60, 60));
    palette.setColor(QPalette::ButtonText,      Qt::white);
    palette.setColor(QPalette::BrightText,      Qt::red);
    palette.setColor(QPalette::Link,            QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight,       QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::black);
    a.setPalette(palette);

    a.setStyleSheet("QToolTip {"
                        "background-image: none;"
                        "background-color: black;"
                        "color: white;"
                        "font-size: 15px;"
                        "border: 1px solid white;"
                    "}");
}

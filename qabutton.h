#ifndef QABUTTON_H
#define QABUTTON_H

// Reference: https://stackoverflow.com/questions/34445507/change-background-color-of-qwidget-using-animation

#include <QtWidgets/QPushButton>
#include <QWidget>

class QAButton : public QPushButton
{

    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    QAButton(QWidget *parent = 0);
    void setColor (QColor color);
    QColor color();
};

#endif // QABUTTON_H

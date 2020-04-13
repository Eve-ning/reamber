#include "qcustomplotmouse.h"

QCustomPlotMouse::QCustomPlotMouse(QWidget *parent) :
    QCustomPlot(parent){}

QCustomPlotMouse::~QCustomPlotMouse()
{

}

void QCustomPlotMouse::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClickEvent(event);
}


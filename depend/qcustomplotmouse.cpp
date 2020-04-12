#include "qcustomplotmouse.h"

QCustomPlotMouse::QCustomPlotMouse(QWidget *parent) :
    QCustomPlot(parent){}

QCustomPlotMouse::~QCustomPlotMouse()
{

}

void QCustomPlotMouse::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        qDebug() << this->xAxis->pixelToCoord(event->pos().x());
        qDebug() << this->yAxis->pixelToCoord(event->pos().y());
    }
}

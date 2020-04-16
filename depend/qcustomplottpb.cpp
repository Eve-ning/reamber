#include "qcustomplottpb.h"

QCustomPlotTPB::QCustomPlotTPB(QWidget *parent) :
    QCustomPlot(parent){}

QCustomPlotTPB::~QCustomPlotTPB()
{

}

void QCustomPlotTPB::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit removeEvent();
}

void QCustomPlotTPB::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        emit addAnchorEvent();
        break;
    case Qt::Key_B:
        emit addBezierEvent();
        break;
    }
}


#include "qcustomplottpb.h"

QCustomPlotTPB::QCustomPlotTPB(QWidget *parent) :
    QCustomPlot(parent){}

QCustomPlotTPB::~QCustomPlotTPB()
{

}

void QCustomPlotTPB::mousePressEvent(QMouseEvent *event)
{
//    if (event->button() == Qt::RightButton) {
//        QPoint pos = this->mapFromGlobal(this->cursor().pos());
//        // Do not convert to coord
//        emit removeEvent(QVector2D(float(pos.x()),
//                                   float(pos.y())));
//    }
}

void QCustomPlotTPB::keyPressEvent(QKeyEvent *event)
{
    QPoint pos = this->mapFromGlobal(this->cursor().pos());

    switch (event->key()) {
    case Qt::Key_A:
        emit addAnchorEvent(QVector2D(float(this->xAxis->pixelToCoord(pos.x())),
                                      float(this->yAxis->pixelToCoord(pos.y()))));
        break;
    case Qt::Key_B:
        emit addBezierEvent(QVector2D(float(this->xAxis->pixelToCoord(pos.x())),
                                      float(this->yAxis->pixelToCoord(pos.y()))));
        break;
    case Qt::Key_Delete:
    case Qt::Key_D:
        emit removeEvent(QVector2D(float(pos.x()),
                                   float(pos.y())));
        break;
    }
}

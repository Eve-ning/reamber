#include "qcustomplottpb.h"

QCustomPlotTPB::QCustomPlotTPB(QWidget *parent) :
    QCustomPlot(parent){

    // Enable dark mode
    xAxis->setBasePen(QPen(Qt::white, 1));
    yAxis->setBasePen(QPen(Qt::white, 1));
    xAxis->setTickPen(QPen(Qt::white, 1));
    yAxis->setTickPen(QPen(Qt::white, 1));
    xAxis->setSubTickPen(QPen(Qt::white, 1));
    yAxis->setSubTickPen(QPen(Qt::white, 1));
    xAxis->setTickLabelColor(Qt::white);
    yAxis->setTickLabelColor(Qt::white);
    xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    xAxis->grid()->setSubGridVisible(true);
    yAxis->grid()->setSubGridVisible(true);
    xAxis->grid()->setZeroLinePen(Qt::NoPen);
    yAxis->grid()->setZeroLinePen(Qt::NoPen);
    xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    setBackground(QColor(53, 53, 53));
    axisRect()->setBackground(QColor(53, 53, 53));

    // Set Dragging and Zoom interaction
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    axisRect(0)->setRangeDrag(Qt::Vertical);
    axisRect(0)->setRangeZoom(Qt::Vertical);
}

QCustomPlotTPB::~QCustomPlotTPB()
{

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

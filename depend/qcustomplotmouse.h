#ifndef QCUSTOMPLOTMOUSE_H
#define QCUSTOMPLOTMOUSE_H

#include "depend/qcustomplot.h"
class QMouseEvent;

class QCustomPlotMouse : public QCustomPlot
{
    Q_OBJECT

    public:
    explicit QCustomPlotMouse(QWidget* parent = nullptr);

    ~QCustomPlotMouse();
protected:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // QCUSTOMPLOTMOUSE_H

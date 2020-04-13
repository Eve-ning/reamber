#ifndef QCUSTOMPLOTMOUSE_H
#define QCUSTOMPLOTMOUSE_H

#include "depend/qcustomplot.h"

class QCustomPlotMouse : public QCustomPlot
{
public:
    Q_OBJECT

    public:
    explicit QCustomPlotMouse(QWidget* parent = nullptr);

    ~QCustomPlotMouse() override;

    void mouseDoubleClickEvent(QMouseEvent * event) override;
protected:
signals:
    void doubleClickEvent(QMouseEvent * event);

};

#endif // QCUSTOMPLOTMOUSE_H

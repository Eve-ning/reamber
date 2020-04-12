#include "include/function/twopointbezier.h"
#include "ui_twopointbezier.h"
#include "depend/qcustomplot.h"
#include <QDebug>
#include <QVector2D>
#include <QtGlobal>

TwoPointBezier::TwoPointBezier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPointBezier)
{
    ui->setupUi(this);
    ui->customplot->addGraph();
    auto vec = createBezier(QVector<double>({0, 1, 9, 10}),
                            QVector<double>({0, 9, 1, 10}),
                            0.01);
    ui->customplot->xAxis->setRange(0, 20);
    ui->customplot->yAxis->setRange(0, 20);
    setCustomPlot(vec);
}

TwoPointBezier::~TwoPointBezier()
{
    delete ui;
}

QVector<QVector2D> TwoPointBezier::createBezier(const QVector<double> &x, const QVector<double> &y, double start, double end, double interval)
{
    // general def
    if (x.size() != y.size()){
        qDebug() << "x and y size must match";
        return QVector<QVector2D>({});
    }

    int size = x.size();
    double sumX = 0.0;
    double sumY = 0.0;
    double t = 0.0;
    int step = 0;

    auto factorial = [](int a) -> int {
        int sum = 1;
        for (int i = 2; i <= a; i ++) sum *= i;
        return sum; // int to double for safer conversion
    };

    QVector<QVector2D> out;

    // API to include ends
    while (t < 1.0) {
        t = (interval * step) / (end - start);

        sumX = 0.0;
        sumY = 0.0;
        for (int p = 0; p < size; p ++) {
            int coeff = factorial(size - 1) / (factorial(p) * factorial(size - p - 1));
            sumX += coeff * pow(1.0 - t, size - p - 1) * pow(t, p)* x[p];
            sumY += coeff * pow(1.0 - t, size - p - 1) * pow(t, p)* y[p];
        }
        out.push_back(QVector2D(float(sumX), float(sumY)));
        step++;
    }


    return out;
}
QVector<QVector2D> TwoPointBezier::createBezier(const QVector<double> &x, const QVector<double> &y, double interval)
{
    return createBezier(x, y,
                        *std::min_element(x.begin(), x.end()),
                        *std::max_element(x.begin(), x.end()),
                        interval);
}

QVector<QVector2D> TwoPointBezier::createBezier(const QVector<QVector2D> &p, double start, double end, double interval){
    QVector<double> x;
    QVector<double> y;

    for (auto i : p) {
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }

    return createBezier(x, y, start, end, interval);
}

QVector<QVector2D> TwoPointBezier::createBezier(const QVector<QVector2D> &p, double interval){
    QVector<double> x;
    QVector<double> y;

    for (auto i : p) {
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }

    return createBezier(x, y,
                        *std::min_element(x.begin(), x.end()),
                        *std::max_element(x.begin(), x.end()),
                        interval);
}

void TwoPointBezier::setCustomPlot(const QVector<double> &x, const QVector<double> &y) {
    auto customplot = ui->customplot;
    customplot->graph(0)->setData(x, y, false);
    customplot->replot();
}

void TwoPointBezier::setCustomPlot(const QVector<QVector2D> &p) {
    QVector<double> x;
    QVector<double> y;

    for (auto i : p) {
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }

    return setCustomPlot(x, y);
}



















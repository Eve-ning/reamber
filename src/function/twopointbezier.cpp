#include "include/function/twopointbezier.h"
#include "ui_twopointbezier.h"
#include "depend/qcustomplot.h"
#include <QVector2D>
#include <QtGlobal>

TwoPointBezier::TwoPointBezier(QWidget *parent) :
    QWidget(parent),
    p(QVector<QVector2D>(4)),
    interval(1000.0),
    ui(new Ui::TwoPointBezier)
{
    ui->setupUi(this);
    ui->customplot->addGraph();
    initP();
}

TwoPointBezier::~TwoPointBezier()
{
    delete ui;
}



QVector<QVector2D> TwoPointBezier::createBezier(double start, double end) {
    int size = p.size();
    double t = start;

    auto factorial = [](int a) -> int {
        int sum = 1;
        for (int i = 2; i <= a; i ++) sum *= i;
        return sum;
    };

    QVector<QVector2D> out;
    std::sort(p.begin(), p.end(), [](QVector2D a, QVector2D b){ return a.x() < b.x(); });

    // API to include ends
    for (int step = 1; t < 1.0; step++) {
        double sumX = 0.0;
        double sumY = 0.0;
        for (int n = 0; n < size; n ++) {
            int coeff = factorial(size - 1) / (factorial(n) * factorial(size - n - 1));
            sumX += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * double(p[n].x());
            sumY += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * double(p[n].y());
        }
        out.push_back(QVector2D(float(sumX), float(sumY)));
        t = (interval * step) / (end - start);
    }
    out.push_back(QVector2D(float(end), float(p.last().y())));

    return out;
}

QVector<QVector2D> TwoPointBezier::createBezier() {
    // Automatically sets start and end
    QVector<double> x = QVector<double>();
    for (const auto & i : p) x.push_back(double(i.x()));
    return createBezier(*std::min_element(x.begin(), x.end()),
                        *std::max_element(x.begin(), x.end()));
}

bool TwoPointBezier::live() const {
    return ui->check_live->isChecked();
}

void TwoPointBezier::updatePlot() {
    if (!live()) return;
    auto customplot = ui->customplot;
    auto vec = createBezier();
    QVector<double> x = QVector<double>();
    QVector<double> y = QVector<double>();
    for (auto i : vec){
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }
    customplot->graph(0)->setData(x, y, false);
    auto xMinMax = std::minmax_element(x.begin(), x.end());
    auto yMinMax = std::minmax_element(y.begin(), y.end());
    customplot->xAxis->setRange(*xMinMax.first * 0.9, *xMinMax.second * 1.1);
    customplot->yAxis->setRange(*yMinMax.first * 0.9, *yMinMax.second * 1.1);
    customplot->replot();
}

void TwoPointBezier::initP()
{
    p[0] = QVector2D(float(ui->x1ms->value()), float(ui->y1ms->value()));
    p[1] = QVector2D(float(ui->x2ms->value()), float(ui->y2ms->value()));
    p[2] = QVector2D(float(ui->x3ms->value()), float(ui->y3ms->value()));
    p[3] = QVector2D(float(ui->x4ms->value()), float(ui->y4ms->value()));
}

void TwoPointBezier::on_y1ms_valueChanged(double arg1){ p[0].setY(float(arg1)); updatePlot(); }
void TwoPointBezier::on_x2ms_valueChanged(double arg1){ p[1].setX(float(arg1)); updatePlot(); }
void TwoPointBezier::on_y2ms_valueChanged(double arg1){ p[1].setY(float(arg1)); updatePlot(); }
void TwoPointBezier::on_x3ms_valueChanged(double arg1){ p[2].setX(float(arg1)); updatePlot(); }
void TwoPointBezier::on_y3ms_valueChanged(double arg1){ p[2].setY(float(arg1)); updatePlot(); }
void TwoPointBezier::on_x4ms_valueChanged(double arg1){ p[3].setX(float(arg1)); updatePlot(); }
void TwoPointBezier::on_y4ms_valueChanged(double arg1){ p[3].setY(float(arg1)); updatePlot(); }
void TwoPointBezier::on_x2p_valueChanged(double arg1){
    auto xms = float(arg1 / 100.0) * (p[3].x() - p[0].x()) + p[0].x();
    p[1].setX(xms);
    ui->x2ms->setValue(double(xms));
    updatePlot();
}
void TwoPointBezier::on_x3p_valueChanged(double arg1){
    auto xms = float(arg1 / 100.0) * (p[3].x() - p[0].x()) + p[0].x();
    p[2].setX(xms);
    ui->x3ms->setValue(double(xms));
    updatePlot();
}
void TwoPointBezier::on_interval_valueChanged(int arg1){ interval = arg1; updatePlot(); }


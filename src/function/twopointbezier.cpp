#include "include/function/twopointbezier.h"
#include "ui_twopointbezier.h"
#include "include/common.h"
#include "depend/qcustomplot.h"
#include "algorithm/algorithm.h"
#include <QVector2D>
#include <QtGlobal>

TwoPointBezier::TwoPointBezier(QWidget *parent) :
    QWidget(parent),
    bezierPts(QVector<QVector2D>(0)),
    anchorPts(QVector<QVector2D>(2)),
    ui(new Ui::TwoPointBezier) {
    ui->setupUi(this);

    initToolTips();

    // Initializes IO
    ui->input->hideKeyWidget();
    ui->input->setTitle("Input");
    ui->input->setPlaceholderText("Variant Input (2 Offsets)");

    // Initializes CustomPlots
    ui->customPlot->addGraph(); // For the function
    ui->customPlot->addGraph(); // For the bezier
    ui->customPlot->addGraph(); // For the anchor

    // Initializes Parameters
    ui->startOffset->setRange(int(OFFSET_MIN), int(OFFSET_MAX));
    ui->endOffset  ->setRange(int(OFFSET_MIN), int(OFFSET_MAX));
    ui->steps      ->setRange(BEZIER_MIN_STEPS, BEZIER_MAX_STEPS);

    ui->startOffset->setValue(0);
    ui->endOffset  ->setValue(1000);
    ui->steps      ->setValue(BEZIER_DEFAULT_STEPS);

    // Connects the double click event
    connect(ui->customPlot, SIGNAL(removeEvent(QVector2D)),
            this,           SLOT  (removePoint(QVector2D)));
    connect(ui->customPlot, SIGNAL(addAnchorEvent(QVector2D)),
            this,           SLOT  (addAnchor(QVector2D)));
    connect(ui->customPlot, SIGNAL(addBezierEvent(QVector2D)),
            this,           SLOT  (addBezier(QVector2D)));

    // Activate SV to initialize as SV
    useSV();
    resetSettings();
    plot();
}

TwoPointBezier::~TwoPointBezier() {
    delete ui;
}

void TwoPointBezier::initToolTips() {
    ui->output->setToolTip("Generated Output goes here");
    ui->input->setToolTip("Update Offset bounds here. Only the first 2 offsets are used");
    ui->updateBoundBtn->setToolTip("Update Bounds with the above input");
    ui->startOffset->setToolTip("Initial Offset, cannot be more or equal to the End Offset");
    ui->endOffset->setToolTip("Final Offset, cannot be more or equal to the Initial Offset");
    ui->startValue->setToolTip("Initial Value");
    ui->endValue->setToolTip("Final Value");
    ui->steps->setToolTip("Steps of Bezier calculation, more steps makes it smoother.");
    ui->svRadio->setToolTip("Change to SV Mode");
    ui->bpmRadio->setToolTip("Change to BPM Mode");
    ui->customPlot->setStatusTip("This is where you edit the function.\n"
                                 "Hover your mouse over and press keys indicated at the top of the plot to create points.\n"
                                 "If it isn't working, click on the plot to focus it.");
    ui->resetButton->setToolTip("Resets most parameters to its original state.");
}

QVector<QVector2D> TwoPointBezier::createPlot() {
    auto anchorPtsCopy = sortByX(anchorPts);

    QVector<QVector2D> points;
    // For each anchor pair
    for (auto anchorI = anchorPtsCopy.begin();
         anchorI < (anchorPtsCopy.end() - 1); anchorI ++) {

        QVector<QVector2D> bezierPtsFilter;
        bezierPtsFilter.push_back(*anchorI);
        bezierPtsFilter.push_back(*(anchorI + 1));

        std::copy_if(bezierPts.begin(), bezierPts.end(), std::back_inserter(bezierPtsFilter),
                     [anchorI](const QVector2D & p) {
            return p.x() >= anchorI->x() &&
                   p.x() < (anchorI + 1)->x();
        });

        if (bezierPtsFilter.size() == 66) bezierPts.pop_back();

        points.append(createBezier(bezierPtsFilter, ui->steps->value(), true));
        // We remove the ends if it's not at the end
        if (anchorI + 2 != anchorPtsCopy.end()) points.pop_back();
    }

    return points;
}

void TwoPointBezier::plot() {
    plotFunction();
    plotAnchor();
    plotBezier();
    warning(); // Generates warnings
}
void TwoPointBezier::plotFunction() {
    auto customPlot = ui->customPlot;

    // Set Bezier Function
    auto vec = createPlot();
    updateAverage(vec);
    QVector<double> x = QVector<double>();
    QVector<double> y = QVector<double>();

    for (auto i : vec){
        x.push_back(double(i.x()));
        y.push_back(double(i.y()));
    }

    customPlot->graph(0)->setData(x, y, false);
    // Set color based on SV or BPM
    QPen pen;
    pen.setColor(ui->svRadio->isChecked() ? Color::GREEN : Color::RED);
    pen.setWidth(2);
    customPlot->graph(0)->setPen(pen);
    customPlot->graph(0)->setBrush(ui->svRadio->isChecked() ?
                                   ColorFade::GREEN : ColorFade::RED);

    // Updates domain
    auto xMinMax = std::minmax_element(x.begin(), x.end());
    updatePlotDomain(*xMinMax.first,*xMinMax.second);

    // Updates range
    // auto yMinMax = std::minmax_element(y.begin(), y.end());
    // updatePlotRange(*yMinMax.first, *yMinMax.second);
}
void TwoPointBezier::plotBezier() {
    auto customPlot = ui->customPlot;

    // Set Bezier Points
    QVector<double> xs = QVector<double>();
    QVector<double> ys = QVector<double>();
    for (auto i : bezierPts){
        xs.push_back(double(i.x()));
        ys.push_back(double(i.y()));
    }

    customPlot->graph(1)->setData(xs, ys, false);

    QPen pen;
    pen.setColor(Color::WHITE);
    pen.setWidth(1);
    customPlot->graph(1)->setPen(pen);
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customPlot->replot();
}
void TwoPointBezier::plotAnchor() {
    auto customPlot = ui->customPlot;

    // Set Bezier Points
    QVector<double> xs = QVector<double>();
    QVector<double> ys = QVector<double>();
    for (auto i : anchorPts){
        xs.push_back(double(i.x()));
        ys.push_back(double(i.y()));
    }

    customPlot->graph(2)->setData(xs, ys, false);
    QPen pen;
    pen.setColor(Color::BLUE);
    pen.setWidth(1);
    customPlot->graph(2)->setPen(pen);
    customPlot->graph(2)->setLineStyle(QCPGraph::lsImpulse);
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));
    customPlot->replot();
}

void TwoPointBezier::warning() {
    if (ui->endOffset->value() - ui->startOffset->value() <= 0)
        ui->startOffset->setStyleSheet(ColorStyleSheet::RED);
    else ui->startOffset->setStyleSheet(ColorStyleSheet::WHITE);
}

void TwoPointBezier::updateAverage(QVector<QVector2D> & pts) {
    double sum = 0.0;
    bool isBpm = ui->bpmRadio->isChecked();
    for (int i = 0; i < (pts.size() - 1); i ++)
        sum += clipValue(double(pts[i].y()),isBpm) * (double(pts[i + 1].x()) - double(pts[i].x()));
    double average = sum / (ui->endOffset->value() - ui->startOffset->value());

    ui->averageLabel->setText(QString("Average: %1x").arg(QString::number(average, 'f', 2)));
}

void TwoPointBezier::updatePlotRange(double min, double max){
    ui->customPlot->yAxis->setRange(min, max);
}
void TwoPointBezier::updatePlotDomain(double min, double max) {
    ui->customPlot->xAxis->setRange(min, max);
}

void TwoPointBezier::updatePointBounds(double newMin, double newMax) {
    // This updates the point bounds relatively instead of removing it on bound update.
    double oldMin = double(anchorPts[0].x());
    double oldMax = double(anchorPts[1].x());
    for (auto & bezierPt : bezierPts)
        bezierPt.setX(float((double(bezierPt.x()) - oldMin) / (oldMax - oldMin) * (newMax - newMin) + newMin));
    for (auto & anchorPt : anchorPts)
        anchorPt.setX(float((double(anchorPt.x()) - oldMin) / (oldMax - oldMin) * (newMax - newMin) + newMin));
}

void TwoPointBezier::useSV() {
    ui->startValue->setValue(SV_DEFAULT);
    ui->startValue->setRange(SV_MIN, SV_MAX);
    ui->startValue->setSuffix(Suffix::SV);
    ui->startValue->setSingleStep(SV_STEPSIZE);
    ui->endValue  ->setValue(SV_DEFAULT);
    ui->endValue  ->setRange(SV_MIN, SV_MAX);
    ui->endValue  ->setSuffix(Suffix::SV);
    ui->endValue  ->setSingleStep(SV_STEPSIZE);
}
void TwoPointBezier::useBPM() {
    ui->startValue->setRange(BPM_MIN, BPM_MAX);
    ui->startValue->setValue(BPM_DEFAULT);
    ui->startValue->setSuffix(Suffix::BPM);
    ui->startValue->setSingleStep(BPM_STEPSIZE);
    ui->endValue  ->setRange(BPM_MIN, BPM_MAX);
    ui->endValue  ->setValue(BPM_DEFAULT);
    ui->endValue  ->setSuffix(Suffix::BPM);
    ui->endValue  ->setSingleStep(BPM_STEPSIZE);
}
void TwoPointBezier::resetSettings() {
    // I don't think resetting offsets is user friendly.
    // ui->startOffset->setValue(0);
    // ui->endOffset  ->setValue(int(OFFSET_INTERVAL_DEFAULT) * 100);
    // ui->interval   ->setValue(int(OFFSET_INTERVAL_DEFAULT));

    ui->steps->setValue(BEZIER_DEFAULT_STEPS);
    anchorPts = QVector<QVector2D>(2);
    anchorPts[0] = {float(ui->startOffset->value()),
                    float(ui->startValue->value())};
    anchorPts[1] = {float(ui->endOffset->value()),
                    float(ui->endValue->value())};
    bezierPts = QVector<QVector2D>();
}

QVector<QVector2D> TwoPointBezier::createBezier(QVector<QVector2D> points, double start, double end, int steps, bool includeEnd) {
    int size = points.size();

    QVector<QVector2D> out;
    std::sort(points.begin(), points.end(),
              [](QVector2D a, QVector2D b){ return a.x() < b.x(); });

    // API to include ends
    double t = 0;
    for (int step = 1; t < 1.0; step++) {
        double sumX = 0.0;
        double sumY = 0.0;
        for (int n = 0; n < size; n ++) {
            long long coeff = binomCoeff(size - 1, n);
            sumX += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * (double(points[n].x()) - start);
            sumY += coeff * pow(1.0 - t, size - n - 1) * pow(t, n) * double(points[n].y());
        }
        out.push_back(QVector2D(float(sumX + start), float(sumY)));
        t = double(step) / steps;
    }
    if (includeEnd) out.push_back(QVector2D(float(end), float(points.last().y())));

    return out;
}
QVector<QVector2D> TwoPointBezier::createBezier(const QVector<QVector2D>& points, int steps, bool includeEnd) {
    QVector<double> x = QVector<double>();
    for (const auto & i : points) x.push_back(double(i.x()));
    return createBezier(points,
                        *std::min_element(x.begin(), x.end()),
                        *std::max_element(x.begin(), x.end()),
                        steps,
                        includeEnd);
}

TimingPointV TwoPointBezier::generateCode(const QVector<double> & offsets,
                                          const QVector<double> & values,
                                          bool isBPM){
    TimingPointV tpV = TimingPointV();
    if (offsets.size() != values.size()){
        qDebug() << "offsets and values must be of the same size";
        return TimingPointV();
    }
    int size = offsets.size();

    TimingPoint tp = TimingPoint();
    for (int i = 0; i < size; i ++) {
        tp.loadParameters(offsets[i], values[i], isBPM);
        tpV.pushBack(tp);
    }
    return tpV;
}

void TwoPointBezier::addAnchor(QVector2D pos) {
    if (pos.x() > ui->endOffset->value() || pos.x() < ui->startOffset->value()) return; // Reject x out of bounds
    anchorPts.push_back(pos);
    plot();
}
void TwoPointBezier::addBezier(QVector2D pos) {
    if (pos.x() > ui->endOffset->value() || pos.x() < ui->startOffset->value()) return; // Reject x out of bounds
    bezierPts.push_back(pos);
    plot();
}
void TwoPointBezier::removePoint(QVector2D pos) {
    auto allPts = anchorPts + bezierPts;
    allPts.removeFirst();
    allPts.removeFirst(); // Don't remove the main anchors

    if (allPts.empty()) return;

    float min = std::numeric_limits<float>::max();
    QVector2D minV = allPts[0];
    for (auto pt : allPts){
        QVector2D ptPixels;
        // Recieved pos is in pixels
        ptPixels.setX(float(ui->customPlot->xAxis->coordToPixel(double(pt.x()))));
        ptPixels.setY(float(ui->customPlot->yAxis->coordToPixel(double(pt.y()))));

        // Compare distance in pixels
        auto dist = (pos - ptPixels).length();

        // If smaller, we set
        if (dist < min) {
            min = dist;
            minV = pt;
        }
    }
    // don't remove if too far
    if (double(min) > REMOVE_DISTANCE_MAX) return;
    if (!anchorPts.removeOne(minV)) // Don't need to execute both
        bezierPts.removeOne(minV);

    plot();
}

void TwoPointBezier::on_generateButton_clicked() {
    auto bez = createPlot();
    QVector<double> offsets = QVector<double>();
    QVector<double> values  = QVector<double>();
    bool isBpm = ui->bpmRadio->isChecked();
    for (const auto & bezI : bez) {
        offsets.push_back(double(bezI.x()));
        values.push_back(clipValue(double(bezI.y()), isBpm));
    }
    ui->output->write(generateCode(offsets, values, ui->bpmRadio->isChecked()));
}
void TwoPointBezier::on_bpmRadio_clicked() {
    resetSettings();
    useBPM();
    updatePlotRange(RANGE_MIN_BPM, RANGE_MAX_BPM);
    plot();
}
void TwoPointBezier::on_svRadio_clicked() {
    resetSettings();
    useSV();
    updatePlotRange(RANGE_MIN_SV, RANGE_MAX_SV);
    plot();
}
void TwoPointBezier::on_startOffset_valueChanged(int arg1) {
    if (arg1 >= ui->endOffset->value()) return;
    updatePointBounds(arg1, ui->endOffset->value());
    plot();
}
void TwoPointBezier::on_endOffset_valueChanged(int arg1) {
    if (arg1 <= ui->startOffset->value()) return;
    updatePointBounds(ui->startOffset->value(), arg1);
    plot();
}
void TwoPointBezier::on_startValue_valueChanged(double arg1) {
    anchorPts[0].setY(float(arg1));
    plot();
}
void TwoPointBezier::on_endValue_valueChanged(double arg1) {
    anchorPts[1].setY(float(arg1));
    plot();
}
void TwoPointBezier::on_updateBoundBtn_clicked() {

    auto offsets = ui->input->readOffsets(true);
    if (offsets.length() < 2) return;

    updatePointBounds(offsets[0], offsets[1]);

    if (offsets[0] > ui->startOffset->value()) {
        ui->endOffset->setValue(int(offsets[1]));
        ui->startOffset->setValue(int(offsets[0]));
    } else {
        ui->startOffset->setValue(int(offsets[0]));
        ui->endOffset->setValue(int(offsets[1]));
    }
    plot();
}
void TwoPointBezier::on_steps_editingFinished() {
    plot();
}
void TwoPointBezier::on_resetButton_clicked(){
    resetSettings();
    plot();
}

void TwoPointBezier::on_output_textChanged() {
    emit outputChanged();
}
QString TwoPointBezier::output() const {
    return ui->output->toPlainText();
}

long long TwoPointBezier::binomCoeff(int n, int k) {
    // defined as n! / k! (n-k)!
    // We find if k or n-k is larger

    // e.g. 15 C 5
    //       n   k

    //    15!
    // --------  = 15 * 14 * ... * 11 / (5!) = 15 / 5 * 14 / 4 ... 11 / 1
    // 5! * 10!    We don't evaluate 15!

    int n_k = n - k;
    long double result = 1;
    int smaller = n_k < k ? n_k : k; // find the smaller number
    while (smaller >= 1) {
        result *= static_cast<long double>(double(n) / double(smaller));
        n--;
        smaller--;
    }
    return static_cast<long long>(result);
}

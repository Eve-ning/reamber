#ifndef COMPILE_H
#define COMPILE_H

#include <QString>
#include <QtWidgets>

#include "defargs.h"
#include "convert.h"

namespace COMPILE {

    //COMPILERS
    QString OM_NN(QString xAxis = DEFARGS::xAxis,
                  QString offset = DEFARGS::offset,
                  QString yAxis = DEFARGS::yAxis,
                  QString extension = DEFARGS::nnExtension);

    QString OM_LN(QString xAxis = DEFARGS::xAxis,
                  QString offset = DEFARGS::offset,
                  QString lnOffset = DEFARGS::lnOffset,
                  QString yAxis = DEFARGS::yAxis,
                  QString lnParameter = DEFARGS::lnParameter,
                  QString extension = DEFARGS::lnExtension);

    QString OM_BPM(QString offset = DEFARGS::offset,
                   QString bpmCode = DEFARGS::bpmCode,
                   QString extension = DEFARGS::bpmExtension);

    QString OM_SV(QString offset = DEFARGS::offset,
                  QString svCode = DEFARGS::svCode,
                  QString extension = DEFARGS::svExtension);

    QString BASIC_HO(QString noOfKeys = DEFARGS::noOfKeys,
                     QString offset = DEFARGS::offset,
                     QString column = DEFARGS::column,
                     QString lnOffset = DEFARGS::lnOffset,
                     QString label = DEFARGS::hitObjectLabel);

    QString BASIC_TP(QString offset = DEFARGS::offset,
                     QString value = DEFARGS::bpmValue,
                     QString timingPointType = DEFARGS::timingPointType,
                     QString label = DEFARGS::timingPointLabel);


    void ProcOutput(QTextBrowser *inputBoxObject, QTextBrowser *outputBoxObject);

}

#endif // COMPILE_H

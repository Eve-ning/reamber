#ifndef CONVERT_H
#define CONVERT_H

#include <QtWidgets>
#include <QString>
#include <QStringList>

#include "check.h"
#include "compile.h"

namespace CONVERT {

    //CONVERTERS
    double COLUMN_CODEtoVALUE(double columnCode,
                                 double noOfKeys);
    double COLUMN_VALUEtoCODE(double columnValue,
                                 double noOfKeys);

    QList<double> EHOtoOFFSETLIST(QString EHO);
    QList<int> EHOtoCOLUMNLIST(QString EHO);

    QList<double> HOtoOFFSETLIST(QStringList HOList);
    QList<int> HOtoCOLUMNLIST(QStringList HOList, int keyCount);
    QStringList HOtoEXTENSIONLIST(QStringList HOList);

    QList<double> TPtoOFFSETLIST(QStringList TPList);
    QList<double> TPtoVALUELIST(QStringList TPList);
    QList<double> TPtoCODELIST(QStringList TPList);

    QList<double> TPtoSVVALUELIST(QStringList TPList);
    QList<double> TPtoBPMVALUELIST(QStringList TPList);
    QList<double> TPtoSVCODELIST(QStringList TPList);
    QList<double> TPtoBPMCODELIST(QStringList TPList);

    double TP_BPMCODEtoVALUE(double TPCode);
    double TP_BPMVALUEtoCODE(double TPValue);

    double TP_SVCODEtoVALUE(double TPCode);
    double TP_SVVALUEtoCODE(double TPValue);

    QStringList OMtoBASIC(QLabel *messageLabel,
                          bool acceptEHO = true,
                          bool acceptHO = true,
                          bool acceptTP = true,
                          QStringList input = {},
                          int noOfKeys = 4);

    QStringList BASICtoOM(QLabel *messageLabel,
                          QStringList input = {});
}

#endif // CONVERT_H

#ifndef CHECK_H
#define CHECK_H

#include <QString>
#include <QtWidgets>

namespace CHECK {

    QString INPUT(QString input);

    bool EHO(QString EHO);
    bool HO(QString HO);
    bool TP(QString TP);

    bool EHO(QPlainTextEdit *box);
    bool HO(QPlainTextEdit *box);
    bool TP(QPlainTextEdit *box);

    bool EHO(QStringList EHOList);
    bool HO(QStringList HOList);
    bool TP(QStringList TPList);

    bool HO_NN(QString HO_NN);
    bool HO_LN(QString HO_LN);
    bool TP_SV(QString TP_SV);
    bool TP_BPM(QString TP_BPM);

}


#endif // CHECK_H

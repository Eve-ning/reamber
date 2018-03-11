#include "com_tp.h"

cOM_TP::cOM_TP()
{
    offset         = 0      ;
    code           = 100    ;
    metronome      = 4      ;
    sampleSet      = 0      ;
    sampleSetIndex = 0      ;
    volume         = 5      ;
    isBPM          = false  ;
    isKiai         = false  ;
}

cOM_TP::cOM_TP(QString TP)
{
    //            [0] [1]              [2][3][4][5][6][7]
    // REFERENCE: 638,231.660231660231,4, 1, 0, 5, 1, 0
    QStringList TP_splitComma;

    TP_splitComma = TP.split("," , QString::KeepEmptyParts);

    if (TP_splitComma.size() == 8)
    {
        offset         = TP_splitComma[0];
        code           = TP_splitComma[1];
        metronome      = TP_splitComma[2];
        sampleSet      = TP_splitComma[3];
        sampleSetIndex = TP_splitComma[4];
        volume         = TP_splitComma[5];
        isBPM          = (TP_splitComma[6] == 1);
        isKiai         = (TP_splitComma[7] == 1);
    }
    else
    {
        STATMSG("Failed to Convert QString.");
        cOM_TP::cOM_TP;
    }
}

void cOM_TP::setOffset        (double newOffset                 ){ offset         = newOffset        ; return; }
void cOM_TP::setCode          (double newCode                   ){ code           = newCode          ; return; }
void cOM_TP::setMetronome     (unsigned short  newMetronome     ){ metronome      = newMetronome     ; return; }
void cOM_TP::setSampleSet     (unsigned short  newSampleSet     ){ sampleSet      = newSampleSet     ; return; }
void cOM_TP::setSampleSetIndex(unsigned short  newSampleSetIndex){ sampleSetIndex = newSampleSetIndex; return; }
void cOM_TP::setVolume        (unsigned short  newVolume        ){ volume         = newVolume        ; return; }
void cOM_TP::setIsBPM         (bool            newIsBPM         ){ isBPM          = newIsBPM         ; return; }
void cOM_TP::setIsKiai        (bool            newIsKiai        ){ isKiai         = newIsKiai        ; return; }

double cOM_TP::getValue() const
{
    double output;
    if (isBPM)
    {
        output = 60000 / code;
    }
    else
    {
        output = -100 / code;
    }
    return output;
}
void   cOM_TP::setValue(double newValue)
{
    // This will indirectly set code instead
    if (isBPM)
    {
        code = 60000 / newValue;
    }
    else
    {
        code = -100 / newValue;
    }
    return;
}

QString cOM_TP::toString()
{
    return      QString::number(offset        ) + ","
            +   QString::number(code          ) + ","
            +   QString::number(metronome     ) + ","
            +   QString::number(sampleSet     ) + ","
            +   QString::number(sampleSetIndex) + ","
            +   QString::number(volume        ) + ","
            +   isBPM  ? 1 : 0                  + ","
            +   isKiai ? 1 : 0 ;
}

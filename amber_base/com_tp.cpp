#include "com_tp.h"

// CONSTRUCTORS
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
    loadFail       = false  ;
}
cOM_TP::cOM_TP(QString TP) : cOM_TP()
{
    loadTP(TP);
}
cOM_TP::cOM_TP(QLineEdit *line) : cOM_TP()
{
    loadTP(line);
}
cOM_TP::cOM_TP(double newOffset, double newValue) : cOM_TP()
{
    loadTP(newOffset, newValue);
}

// LOADERS
void cOM_TP::loadTP(QString TP)
{
    omInfo info;

    cOM_Common::whatOM_Type(info, TP);

    if (!info.getIsTP())
    {
        cOM_Common::assertTP(TP);
        loadFail = true;
        return;
    }

    //            [0] [1]              [2][3][4][5][6][7]
    // REFERENCE: 638,231.660231660231,4, 1, 0, 5, 1, 0

    QStringList TP_splitComma;

    TP_splitComma = TP.split("," , QString::KeepEmptyParts);

    if (TP_splitComma.size() == 8)
    {
        offset         = TP_splitComma[0].toDouble();
        code           = TP_splitComma[1].toDouble();
        metronome      = TP_splitComma[2].toInt();
        sampleSet      = TP_splitComma[3].toInt();
        sampleSetIndex = TP_splitComma[4].toInt();
        volume         = TP_splitComma[5].toInt();
        isBPM          = (TP_splitComma[6] == "1");
        isKiai         = (TP_splitComma[7] == "1");
    }
    else
    {
        loadFail = true;
    }
}
void cOM_TP::loadTP(QLineEdit *line)
{
    QString lineText;

    lineText = line->text();

    loadTP(lineText);

}
void cOM_TP::loadTP(double newOffset, double newValue)
{
    offset = newOffset;
    setValue(newValue);
}

void cOM_TP::setOffset(double newOffset)
{
    cOM_Common::assertOffsetValid(newOffset);
    offset = newOffset;
}

// SETTERS
void cOM_TP::setValue(double newValue)
{
    cOM_Common::assertDivByZero(newValue);

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

// GETTERS
void    cOM_TP::getInfo () const
{
    qDebug() << "\r\n"
             << "[---- Timing Point Info ----]"       << "\r\n"
             << "OFFSET         : " << offset         << "\r\n"
             << "CODE           : " << code           << "\r\n"
             << "METRONOME      : " << metronome      << "\r\n"
             << "SAMPLESET      : " << sampleSet      << "\r\n"
             << "SAMPLESETINDEX : " << sampleSetIndex << "\r\n"
             << "VOLUME         : " << volume         << "\r\n"
             << "ISBPM          : " << isBPM          << "\r\n"
             << "ISKIAI         : " << isKiai         << "\r\n";
}
double  cOM_TP::getValue() const
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
QString cOM_TP::toString() const
{
    return      QString::number(offset        ) + ","
            +   QString::number(code          ) + ","
            +   QString::number(metronome     ) + ","
            +   QString::number(sampleSet     ) + ","
            +   QString::number(sampleSetIndex) + ","
            +   QString::number(volume        ) + ","
            +   (isBPM  ? "1" : "0")                  + ","
            +   (isKiai ? "1" : "0") ;
}

// OPERS
void cOM_TP::multiplyValue(const cOM_TP rhsOM_TP, bool limitFlag)
{
    setValue(getValue() * rhsOM_TP.getValue());
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::divideValue(const cOM_TP rhsOM_TP, bool limitFlag)
{
    cOM_Common::assertDivByZero(rhsOM_TP.getValue());

    setValue(getValue() / rhsOM_TP.getValue());
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::addValue(const cOM_TP rhsOM_TP, bool limitFlag)
{
    setValue(getValue() + rhsOM_TP.getValue());
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::subtractValue(const cOM_TP rhsOM_TP, bool limitFlag)
{
    setValue(getValue() - rhsOM_TP.getValue());
    if (limitFlag)
    {
        limitValues();
    }
}

void cOM_TP::multiplyValue  (const double rhsDouble, bool limitFlag)
{
    setValue(getValue() * rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::divideValue    (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertDivByZero(rhsDouble);

    setValue(getValue() / rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::addValue       (const double rhsDouble, bool limitFlag)
{
    setValue(getValue() + rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::subtractValue  (const double rhsDouble, bool limitFlag)
{
    setValue(getValue() - rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}

void cOM_TP::multiplyOffset (const double rhsDouble, bool limitFlag)
{
    setOffset(getOffset() * rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::divideOffset   (const double rhsDouble, bool limitFlag)
{
    cOM_Common::assertDivByZero(rhsDouble);

    setOffset(getOffset() * rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::addOffset      (const double rhsDouble, bool limitFlag)
{
    setOffset(getOffset() * rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}
void cOM_TP::subtractOffset (const double rhsDouble, bool limitFlag)
{
    setOffset(getOffset() * rhsDouble);
    if (limitFlag)
    {
        limitValues();
    }
}

// MISC
void cOM_TP::limitValues(double maxSV, double minSV, double maxBPM, double minBPM)
{
    // Make sure min < max
    if ((maxSV != 0 && minSV != 0) && (minSV > maxSV))
    {
        qDebug() << __FUNCTION__ << "minSV > maxSV: " << minSV << " > " << maxSV;
        return;
    }

    if ((maxBPM != 0 && minBPM != 0) && (minBPM > maxBPM))
    {
        qDebug() << __FUNCTION__ << "minBPM > maxBPM: " << minBPM << " > " << maxBPM;
        return;
    }

    // If any value is exactly 0, we take it that the user doesn't want to limit it.
    if (isBPM)
    {
        // BOUND 0 ~ infinity
        if ((minBPM != 0) && (getValue() < minBPM))
        {
            setValue(minBPM);
        }
        else if ((maxBPM != 0) && getValue() > maxBPM)
        {
            setValue(maxBPM);
        }
    } else
    { //isSV
        // BOUND 0.1 ~ 10.0
        if ((minSV != 0) && getValue() < minSV)
        {
            setValue(minSV);
        }
        else if ((maxBPM != 0) && getValue() > maxSV)
        {
            setValue(maxSV);
        }
    }
}

void cOM_TP::limitOffset(double minOffset, double maxOffset)
{
    if (offset > maxOffset)
    {
        setOffset(minOffset);
    }
    else if (offset < minOffset)
    {
        setOffset(minOffset);
    }
}




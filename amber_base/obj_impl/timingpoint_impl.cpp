#include "amber_base/obj_impl/TimingPoint_impl.h"

TimingPoint_impl::TimingPoint_impl():
    offset (0),
    timeCode (std::make_shared<SliderVelocity>(SliderVelocity())),
    metronome (4),
    sampleSet (SampleSet::SAMPLE_SET::AUTO),
    sampleSetIndex (0),
    volume (5),
    isKiai (false)
{

}

// LOADERS
void TimingPoint_impl::loadTP(const QString &TP)
{
    if (!ValidObj::timingPoint(TP)) // Case: Invalid
    {
        loadFail = true;
        AmberException(AmberException::TP_LOADFAIL, QString("Input: ") + TP);
        return;
    }

    //            [0] [1]              [2][3][4][5][6][7]
    // REFERENCE: 638,231.660231660231,4, 1, 0, 5, 1, 0

    // convert to stream parsing

    QStringList TP_splitComma;

    TP_splitComma = TP.split(",", QString::KeepEmptyParts);

    if (TP_splitComma.size() == 8)
    {
        offset = TP_splitComma[0].toDouble();
        metronome = TP_splitComma[2].toInt();
        sampleSet = TP_splitComma[3].toInt();
        sampleSetIndex = TP_splitComma[4].toInt();
        volume = TP_splitComma[5].toInt();
        isKiai = (TP_splitComma[7] == "1");

        // Check if it's BPM
        if (TP_splitComma[6] == "1") {
            timeCode = std::make_shared<BPM>(BPM(TP_splitComma[1].toDouble()));
        } else {
            timeCode = std::make_shared<SliderVelocity>(SliderVelocity(TP_splitComma[1].toDouble()));
        }
    }
    else
    {
        loadFail = true;
        AmberException(AmberException::UNEXPECTED_ERROR, QString("Within this context ") + __FUNCTION__);
        return;
    }
}
void TimingPoint_impl::loadTP(QLineEdit* line)
{
    QString lineText;
    lineText = line->text();
    loadTP(lineText);
}
void TimingPoint_impl::loadTP(Offset offset_, double value_, bool isBPM_)
{
    offset = offset_;
    setType(isBPM_);
    setValue(value_);
}

void TimingPoint_impl::convertToSV(const BPM &referenceValue){
    // We convert this Timing Point into SV, it shouldn't affect visual gameplay

    if (!getIsBPM())
    {
        qDebug() << "Timing Point is already an SV";
    }
    else {
        double value = timeCode->value() / referenceValue.value();
        setType(false);
        setValue(value);
    }
}
void TimingPoint_impl::convertToBPM(const BPM &referenceValue){
    // We convert this Timing Point into BPM, it shouldn't affect visual gameplay

    if (getIsBPM())
    {
        qDebug() << "Timing Point is already a BPM";
    }
    else {
        double value = timeCode->value() / referenceValue.value();
        setType(true);
        setValue(value);
    }
}

void TimingPoint_impl::setType(bool isBPM)
{
    // case: current = BPM, set = SV
    if (getIsBPM() && !isBPM) {
        timeCode = std::make_shared<SliderVelocity>(SliderVelocity());
    }
    // case: current = SV, set = BPM
    else if (getIsSV() && isBPM) {
        timeCode = std::make_shared<BPM>(BPM());
    }
}

void TimingPoint_impl::setValue(double value){
    timeCode->setValue(value);
}

// GETTERS
void TimingPoint_impl::getInfo() const
{
    qDebug() << "\r\n"
             << "[---- Timing Point Info ----]"
             << "\r\n"
             << "OFFSET         : " << QString(offset        ) << "\r\n"
             << "CODE           : " << QString(*timeCode     ) << "\r\n"
             << "METRONOME      : " << QString(metronome     ) << "\r\n"
             << "SAMPLESET      : " << QString(sampleSet     ) << "\r\n"
             << "SAMPLESETINDEX : " << QString(sampleSetIndex) << "\r\n"
             << "VOLUME         : " << QString(volume        ) << "\r\n"
             << "ISBPM          : " << getIsBPM() << "\r\n"
             << "ISKIAI         : " << QString(isKiai        ) << "\r\n";
}
double TimingPoint_impl::getValue() const
{
    return timeCode->value();
}
QString TimingPoint_impl::toString() const
{

    return QString(offset) + "," +
           QString(*timeCode) + "," +
           QString(metronome) + "," +
           QString(sampleSet) + "," +
           QString(sampleSetIndex) + "," +
           QString(volume) + "," +
           (getIsBPM() ? "1" : "0") + "," +
           (isKiai ? "1" : "0");
}




// OPERS


// MISC
//void TimingPoint_impl::limitValues(double maxSV, double minSV, double maxBPM, double minBPM)
//{
//    // Make sure min < max
//    if ((maxSV != 0 && minSV != 0) && (minSV > maxSV))
//    {
//        AExc(
//            AExc::GENERAL_ERROR, QString(__FUNCTION__) + "minSV > maxSV: " + minSV + " > " + maxSV);
//    }

//    if ((maxBPM != 0 && minBPM != 0) && (minBPM > maxBPM))
//    {
//        AExc(AExc::GENERAL_ERROR,
//            QString(__FUNCTION__) + "minBPM > maxBPM: " + minBPM + " > " + maxBPM);
//    }

//    // If any value is exactly 0, we take it that the user doesn't want to limit it.
//    if (isBPM)
//    {
//        // BOUND 0 ~ infinity
//        if ((minBPM != 0) && (getValue() < minBPM))
//        {
//            setValue(minBPM);
//        }
//        else if ((maxBPM != 0) && getValue() > maxBPM)
//        {
//            setValue(maxBPM);
//        }
//    }
//    else
//    { // isSV
//        // BOUND 0.1 ~ 10.0
//        if ((minSV != 0) && getValue() < minSV)
//        {
//            setValue(minSV);
//        }
//        else if ((maxBPM != 0) && getValue() > maxSV)
//        {
//            setValue(maxSV);
//        }
//    }
//}

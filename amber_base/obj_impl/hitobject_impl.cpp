#include "amber_base/obj_impl/hitobject_impl.h"

HitObject_impl::HitObject_impl():
    column(0),
    yAxis (192),
    noteType (NoteType::NOTE_TYPE::NORMAL_NOTE),
    hitsoundType (SampleSet::SAMPLE_SET::AUTO),
    lnEnd (0),
    sampleSet (SampleSet::SAMPLE_SET::AUTO),
    addition (SampleSet::SAMPLE_SET::AUTO),
    customSet (SampleSet::SAMPLE_SET::AUTO),
    volume (0),
    hitsoundFile (""),
    keys (4),
    offset (100)
{

}

// LOADERS
void HitObject_impl::loadHO(const Offset &offset_,
                            const Column &column_,
                            const Keys &keys_)
{
    offset = offset_;
    keys = keys_;
    column = column_;
}
void HitObject_impl::loadHO(const QLineEdit* line,
                       const int& keys_)
{
    QString newOM_HO;
    newOM_HO = line->text();

    loadHO(newOM_HO, keys_);
}


void HitObject_impl::loadHO(const QString& HO,
                       const int& keys_)
{
    if (!ValidObj::hitObject(HO)) // Case: Invalid
    {
        loadFail = true;
        AmberException(AmberException::HO_LOADFAIL, QString("Input: ") + HO);
        return;
    }

    // Case: HO

    /* REFERENCE FOR .osu HO
    // NN

    // splitComma [0] [1] [2]  [3][4]
    // splitColon                     [0][1][2][3][4]
    // REFERENCE  448,192,1799,5, 6,  1: 1: 2: 70:audio.mp3

    // LN

    // splitComma [0] [1] [2]  [3][4]
    // splitColon                    [0]  [1][2][3][4][5]
    // REFERENCE  448,192,1799,5, 6, 2001:1: 1: 2: 70:audio.mp3
    */

    QString str = HO;
    QTextStream inStr(&str);

    int     xAxis_        ;
    int     yAxis_        ;
    double  offset_       ;
    int     noteType_     ;
    int     hitsoundType_ ;
    double  lnEnd_        ;
    int     sampleSet_    ;
    int     addition_     ;
    int     customSet_    ;
    int     volume_       ;
    QString hitsoundFile_;

    QChar  cm_1, cl_1,
           cm_2, cl_2,
           cm_3, cl_3,
           cm_4, cl_4,
           cm_5, cl_5;

    // Stream into values
    switch (std::count(str.begin(),
               str.end(),
               ':'))
    {
    case 4: // NN

        // REFERENCE  448,192,1799,5, 6,  1: 1: 2: 70:audio.mp3
        inStr >> xAxis_         >> cm_1
              >> yAxis_         >> cm_2
              >> offset_        >> cm_3
              >> noteType_      >> cm_4
              >> hitsoundType_  >> cm_5
              >> sampleSet_     >> cl_1
              >> addition_      >> cl_2
              >> customSet_     >> cl_3
              >> volume_        >> cl_4
              >> hitsoundFile_;


        if (cm_1 != ',' || cl_1 != ':' ||
            cm_2 != ',' || cl_2 != ':' ||
            cm_3 != ',' || cl_3 != ':' ||
            cm_4 != ',' || cl_4 != ':' ||
            cm_5 != ',')
        {
             AmberException(AmberException::HO_LOADFAIL, HO);
        }

        break;
    case 5: // LN

        // REFERENCE  448,192,1799,5, 6, 2001:1: 1: 2: 70:audio.mp3
        inStr >> xAxis_        >> cm_1
              >> yAxis_        >> cm_2
              >> offset_       >> cm_3
              >> noteType_     >> cm_4
              >> hitsoundType_ >> cm_5
              >> lnEnd_        >> cl_1
              >> sampleSet_    >> cl_2
              >> addition_     >> cl_3
              >> customSet_    >> cl_4
              >> volume_       >> cl_5
              >> hitsoundFile_;

        if (cm_1 != ',' || cl_1 != ':' ||
            cm_2 != ',' || cl_2 != ':' ||
            cm_3 != ',' || cl_3 != ':' ||
            cm_4 != ',' || cl_4 != ':' ||
            cm_5 != ',' || cl_5 != ':')
        {
            AmberException(AmberException::HO_LOADFAIL, HO);
        }

        break;
    }

    keys         = Keys(keys_);
    column       = Column(XAxis(xAxis_), Keys(keys_));
    yAxis        = YAxis(yAxis_);
    offset       = Offset(offset_);
    noteType     = NoteType(NoteType::NOTE_TYPE(noteType_));
    hitsoundType = SampleSet(SampleSet::SAMPLE_SET(hitsoundType_));
    lnEnd        = Offset(lnEnd_);
    sampleSet    = SampleSet(SampleSet::SAMPLE_SET(sampleSet_));
    addition     = SampleSet(SampleSet::SAMPLE_SET(addition_));
    customSet    = SampleSet(SampleSet::SAMPLE_SET(customSet_));
    volume       = Volume(volume_);
    hitsoundFile = HitsoundFile(hitsoundFile_);


    /* Old Method
     * HO_splitComma = HO.split(",", QString::KeepEmptyParts);
    *    HO_splitColon = HO_splitComma[HO_splitComma.size() - 1].split(":", QString::KeepEmptyParts);
    *
    *
    *
    *    if (HO_splitColon.size() == 5 && HO_splitComma.size() == 6) // Means it is a NN
    *    {
    *
    *
    *
    *
    *        // Assignment to Values
    *        column = Column(XAxis(HO_splitComma[0].toInt()), keys);
    *        yAxis = (HO_splitComma[1]).toInt();
    *        offset = (HO_splitComma[2]).toDouble();
    *        noteType = (HO_splitComma[3]).toInt();
    *        hitsoundType = (HO_splitComma[4]).toInt();
    *        sampleSet = (HO_splitColon[0]).toInt();
    *        addition = (HO_splitColon[1]).toInt();
    *        customSet = (HO_splitColon[2]).toInt();
    *        volume = (HO_splitColon[3]).toInt();
    *        hitsoundFile = (HO_splitColon[4]);
    *
    *        // Default lnEnd Value
    *        lnEnd = -1;
    *    }
    *    else if (HO_splitColon.size() == 6 && HO_splitComma.size() == 6) // Means it is a LN
    *    {
    *        // Assignment to Values
    *        xAxis = (HO_splitComma[0]).toInt();
    *        yAxis = (HO_splitComma[1]).toInt();
    *        offset = (HO_splitComma[2]).toDouble();
    *        noteType = (HO_splitComma[3]).toInt();
    *        hitsoundType = (HO_splitComma[4]).toInt();
    *        lnEnd = (HO_splitColon[0]).toDouble();
    *        sampleSet = (HO_splitColon[1]).toInt();
    *        addition = (HO_splitColon[2]).toInt();
    *        customSet = (HO_splitColon[3]).toInt();
    *        volume = (HO_splitColon[4]).toInt();
    *        hitsoundFile = (HO_splitColon[5]);
    *    }
    *    else
    *    {
    *        loadFail = true;
    *        AExc(AExc::UNEXPECTED_ERROR, QString("Within this context ") + __FUNCTION__);
    *        return;
       }*/
}


// GETTERS
void HitObject_impl::printInfo() const
{
//    qDebug() << ("[---- Hit Object Info ----]") << '\n'
//             << ("COLUMN       : " + QString(column)) << '\n'
//             << ("YAXIS        : " + QString(yAxis)) << '\n'
//             << ("OFFSET       : " + QString(offset)) << '\n'
//             << ("NOTETYPE     : " + QString(noteType)) << '\n'
//             << ("HITSOUNDTYPE : " + QString(hitsoundType)) << '\n'
//             << ("LNEND        : " + QString(lnEnd)) << '\n'
//             << ("SAMPLESET    : " + QString(sampleSet)) << '\n'
//             << ("ADDITION     : " + QString(addition)) << '\n'
//             << ("CUSTOMSET    : " + QString(customSet)) << '\n'
//             << ("VOLUME       : " + QString(volume)) << '\n'
//             << ("HITSOUNDFILE : " + hitsoundFile) << '\n'
//             << ("KEYS         : " + QString(keys)) << '\n';
}
QString HitObject_impl::toString() const
{
    return QString(column.toXAxis(keys)) + "," +
           QString(yAxis) + "," +
           QString(offset) + "," +
           QString(noteType) + "," +
           QString(hitsoundType) + "," +
           (double(lnEnd) == -1 ? "" : (QString(lnEnd) + ":")) +
           QString(sampleSet) + ":" + QString(addition) + ":" +
           QString(customSet) + ":" +
           QString(volume) + ":" + hitsoundFile;
}

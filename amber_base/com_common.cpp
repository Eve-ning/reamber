#include "com_common.h"

cOM_Common::cOM_Common()
{

}

cOM_Common::HOFlag cOM_Common::isHO(QTextBrowser   *tb)
{
    return isHO(tb->toPlainText());
}
cOM_Common::HOFlag cOM_Common::isHO(QLineEdit      *line)
{
    return isHO(line->text());
}
cOM_Common::HOFlag cOM_Common::isHO(QPlainTextEdit *pte)
{
    return isHO(pte->toPlainText());
}
cOM_Common::HOFlag cOM_Common::isHO(QString HO)
{
    QStringList HOSplit;

    HOSplit = HO.split("\n", QString::SkipEmptyParts);

    return isHO(HOSplit);
}
cOM_Common::HOFlag cOM_Common::isHO(QStringList HOList)
{
    QString temp;

    cOM_Common::HOFlag HOType;

    if (HOList[0].split(",").count() != 6 || // All HO has 5 commas
        HOList[0].split(":").count() < 5 || // HO_NN has 4 colons
        HOList[0].split(":").count() > 6)   // HO_LN has 5 colons
    {
//        qDebug() << __FUNCTION__ << "Invalid Input: " << HOList[0];
        return cOM_Common::HOFlag::INVALID;
    }

    switch (HOList[0].split(":").count()) {
    // HO_NN has 4 colons
    // HO_LN has 5 colons
    case 5:
        HOType = cOM_Common::HOFlag::NN_ONLY;
        break;
    case 6:
        HOType = cOM_Common::HOFlag::LN_ONLY;
        break;
    default:
        qDebug() << __FUNCTION__ << "An unexpected error has occurred.";
        break;
    }

    foreach (temp, HOList) {

        if (temp.split(",").count() != 6 || // All HO has 5 commas
            temp.split(":").count() < 5 || // HO_NN has 4 colons
            temp.split(":").count() > 6)   // HO_LN has 5 colons
        {
            qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
            return cOM_Common::HOFlag::INVALID;
        }

        switch (temp.split(":").count())
        {
        // HO_NN has 4 colons
        // HO_LN has 5 colons
        case 5:
            if (HOType != cOM_Common::HOFlag::NN_ONLY &&
                HOType != cOM_Common::HOFlag::NN_LN_ONLY)
            {
                HOType = cOM_Common::HOFlag::NN_LN_ONLY;
            };
            break;
        case 6:
            if (HOType != cOM_Common::HOFlag::LN_ONLY &&
                HOType != cOM_Common::HOFlag::NN_LN_ONLY)
            {
                HOType = cOM_Common::HOFlag::NN_LN_ONLY;
            };
            break;
        default:
            qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
            return cOM_Common::HOFlag::INVALID;
            break;
        }

    } // foreach (temp, HOList)

    return HOType;

}

cOM_Common::TPFlag cOM_Common::isTP(QTextBrowser   *tb)
{
    return isTP(tb->toPlainText());
}
cOM_Common::TPFlag cOM_Common::isTP(QLineEdit      *line)
{
    return isTP(line->text());
}
cOM_Common::TPFlag cOM_Common::isTP(QPlainTextEdit *pte)
{
    return isTP(pte->toPlainText());
}
cOM_Common::TPFlag cOM_Common::isTP(QString TP)
{
    QStringList TPSplit;

    TPSplit = TP.split("\n", QString::SkipEmptyParts);

    return isTP(TPSplit);
}
cOM_Common::TPFlag cOM_Common::isTP(QStringList TP)
{
    QString temp;

    cOM_Common::TPFlag TPType;

    if (TP[0].split(",").count() != 8) // All TP must have 7 commas
    {
//        qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
        return cOM_Common::TPFlag::INVALID;
    }

    switch (TP[0].split(",")[6].toInt()) {
    // All TP will have a parameter on the 7th index that indicates the type
    case 0:
        TPType = cOM_Common::TPFlag::SV_ONLY;
        break;

    case 1:
        TPType = cOM_Common::TPFlag::BPM_ONLY;
        break;

    default:
        // If input has somehow has the wrong value we put it as INVALID
        qDebug() << __FUNCTION__ << "Invalid Input: " << TP[0];
        return cOM_Common::TPFlag::INVALID;
        break;
    }
    // ---

    foreach (temp, TP) {

        if (temp.split(",").count() != 8) // All TP must have 7 commas
        {
            qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
            return cOM_Common::TPFlag::INVALID;
        }

        switch (temp.split(",")[6].toInt()) {
        // All TP will have a parameter on the 7th index that indicates the type
        case 0:
            if (TPType != cOM_Common::TPFlag::SV_ONLY &&
                TPType != cOM_Common::TPFlag::SV_BPM_ONLY)
            {
                TPType = cOM_Common::TPFlag::SV_BPM_ONLY;
            } // If input has 2 different types we set it to SV_BPM_ONLY
            break;

        case 1:
            if (TPType != cOM_Common::TPFlag::BPM_ONLY &&
                TPType != cOM_Common::TPFlag::SV_BPM_ONLY)
            {
                TPType = cOM_Common::TPFlag::SV_BPM_ONLY;
            } // If input has 2 different types we set it to SV_BPM_ONLY
            break;

        default:
            // If input has somehow has the wrong value we put it as INVALID
            qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
            return cOM_Common::TPFlag::INVALID;
            break;
        }
    }

    return TPType;
}

cOM_Common::EHOFlag cOM_Common::isEHO(QTextBrowser   *tb)
{
    return isEHO(tb->toPlainText());
}
cOM_Common::EHOFlag cOM_Common::isEHO(QLineEdit      *line)
{
    return isEHO(line->text());
}
cOM_Common::EHOFlag cOM_Common::isEHO(QPlainTextEdit *pte)
{
    return isEHO(pte->toPlainText());
}
cOM_Common::EHOFlag cOM_Common::isEHO(QString EHO)
{
    // Reference: 01:52:511 (112511|3) -

    QStringList EHOSplit;

    EHOSplit = EHO.split("\n", QString::SkipEmptyParts);

    return isEHO(EHOSplit);
}
cOM_Common::EHOFlag cOM_Common::isEHO(QStringList EHO)
{
    // Reference: 01:52:511 (112511|3) -
    QString temp;

    short colonIndex,
          openBrIndex,
          pipeIndex,
          closeBrIndex;

    foreach (temp, EHO) {

        colonIndex   = temp.indexOf(":");
        openBrIndex  = temp.indexOf("(");
        pipeIndex    = temp.indexOf("|");
        closeBrIndex = temp.indexOf(")");

        if (
            colonIndex   < 0 ||
            openBrIndex  < 0 ||
            pipeIndex    < 0 ||
            closeBrIndex < 0 || // If index is -1, means that the character does not exist.

            colonIndex   > openBrIndex  ||
            openBrIndex  > pipeIndex    ||
            pipeIndex    > closeBrIndex ||
            closeBrIndex < colonIndex   // As the indexes should be increasing, all of these conditions shouldn't be true
           )
        {
//            qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
            return cOM_Common::EHOFlag::INVALID;
        }
    }
    return cOM_Common::EHOFlag::EHO_ONLY;
}

cOM_Common::OMFlag cOM_Common::isOM_Type(QTextBrowser *tb)
{
    return isOM_Type(tb->toPlainText());
}
cOM_Common::OMFlag cOM_Common::isOM_Type(QLineEdit *line)
{
    return isOM_Type(line->text());
}
cOM_Common::OMFlag cOM_Common::isOM_Type(QPlainTextEdit *pte)
{
    return isOM_Type(pte->toPlainText());
}
cOM_Common::OMFlag cOM_Common::isOM_Type(QString input)
{
    QStringList inputSplit;

    inputSplit = input.split("\n", QString::SkipEmptyParts);

    return isOM_Type(inputSplit);
}
cOM_Common::OMFlag cOM_Common::isOM_Type(QStringList input)
{
    if (input.isEmpty())
    {
        qDebug() << __FUNCTION__ << " recieved empty input.";
        return cOM_Common::OMFlag::INVALID;
    }

    QString temp = input[0];

    cOM_Common::OMFlag typeFlag;

    if (isEHO(temp) != cOM_Common::EHOFlag::INVALID)
    {
        typeFlag = cOM_Common::OMFlag::EHO_ONLY;
    } else if (isHO(temp) != cOM_Common::HOFlag::INVALID)
    {
        typeFlag = cOM_Common::OMFlag::HO_ONLY;
    } else if (isTP(temp) != cOM_Common::TPFlag::INVALID)
    {
        typeFlag = cOM_Common::OMFlag::TP_ONLY;
    } else
    {
        return cOM_Common::OMFlag::INVALID;
    }

    foreach (temp, input) {

        if (typeFlag != cOM_Common::OMFlag::MULTIPLETYPES)
        { // We enclose it within an IF statement so to not execute these calls redundantly
            if (
                    (
                        (typeFlag    == cOM_Common::OMFlag::EHO_ONLY) &&
                        (isEHO(temp) != cOM_Common::EHOFlag::INVALID   )
                        ) ||
                    (
                        (typeFlag    == cOM_Common::OMFlag::HO_ONLY) &&
                        (isHO(temp) != cOM_Common::HOFlag::INVALID   )
                        ) ||
                    (
                        (typeFlag    == cOM_Common::OMFlag::TP_ONLY) &&
                        (isTP(temp) != cOM_Common::TPFlag::INVALID   )
                        )
                    )
            {
                // Cases where checks match
                continue; // Continue foreach Loop
            }

        }

        if (
            (
             (isEHO(temp) == cOM_Common::EHOFlag::INVALID) &&
             (isHO(temp)  == cOM_Common::HOFlag::INVALID ) &&
             (isTP(temp)  == cOM_Common::TPFlag::INVALID )
            )
           )
        {
            // Cases where nothing matches
            qDebug() << __FUNCTION__ << "Invalid Input: " << temp;
            return cOM_Common::OMFlag::INVALID;

        } else {
            // We assume other cases to be where there are multiple types
            typeFlag = cOM_Common::OMFlag::MULTIPLETYPES;
        }
    }

    return typeFlag;
}

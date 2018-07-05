#include "amber_base/obj_impl/hitobjectlist_impl.h"

HitObjectList_impl::HitObjectList_impl()
{

}

// LOADERS
void HitObjectList_impl::loadHOList(QList<HitObject> newHOList)
{
    hitObjectList = newHOList;
}
void HitObjectList_impl::loadHOList(QTextBrowser* tb, Keys newKeys)
{
    QString str = tb->toPlainText();
    loadHOList(str, newKeys);
}
void HitObjectList_impl::loadHOList(QLineEdit* line, Keys newKeys)
{
    QString str = line->text();
    loadHOList(str, newKeys);
}
void HitObjectList_impl::loadHOList(QPlainTextEdit* pte, Keys newKeys)
{
    QString str = pte->toPlainText();
    loadHOList(str, newKeys);
}
void HitObjectList_impl::loadHOList(QString& HO_, Keys newKeys)
{
    bool boolEHO, boolHO;

    boolEHO = ValidObj::editorHitObject(HO_);
    boolHO = ValidObj::hitObject(HO_);
    // note that EHO will return true also so we use the EHO case first

    if (boolEHO) // Case: EHO
    {
        loadEHOList(HO_, newKeys); // Pass to EHO Handler
        return;
    }
    else if (boolHO) // Case: HO
    {
        // Convert to StringList and pass towards QStringList Handler
        QStringList HOList;
        HOList = HO_.split('\n', QString::SkipEmptyParts);

        loadHOList(HOList); // Pass to QStringList Handler
    }
    else // Case: Invalid
    {
        loadFail = true;

        AmberException(AmberException::HO_LOADFAIL, QString("Input: ") + HO_);
        return;
    }
}
void HitObjectList_impl::loadHOList(QStringList& HOList, Keys newKeys)
{
    QString HO;
    foreach (HO, HOList)
    {
        hitObjectList.append(HitObject(HO, newKeys));
    }

    return;
}
void HitObjectList_impl::loadEHOList(QString& EHO, Keys newKeys)
{
    // !! DO NOT CALL THIS DIRECTLY
    // Load via loadHOList (QString, int)
    //    QString EHO_trim, EHO_eachSplitComma;
    //    QStringList EHO_splitComma;
    //    QList<double> EHO_splitPipeOffset;
    //    QList<int> EHO_splitPipeColumn;
    //    int openBracketIndex, closeBracketIndex;

    // 00:19:296 (19296|1,19546|2,19671|1,19921|2) -
    QTextStream inStr(&EHO);
    QChar char_;
    int int_0,
        int_1;

    // Find open bracket
    while (char_ != '(' && !inStr.atEnd())
    {
        inStr >> char_;
    }

    // Data Extraction
    while (!inStr.atEnd()){

        // Throw into int (0)
        inStr >> int_0;
        inStr >> char_;

        // Throw into int (1)
        inStr >> int_1;
        inStr >> char_;

        hitObjectList.append(HitObject(Offset(int_0), Column(int_1), newKeys));

        if (char_ == ')')
        {
            return;
        }
    }

    return;


//    openBracketIndex = EHO.indexOf("(");
//    closeBracketIndex = EHO.indexOf(")");

//    EHO_trim = EHO.mid(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

//    EHO_splitComma = EHO_trim.split(",", QString::SkipEmptyParts);

//    foreach (EHO_eachSplitComma, EHO_splitComma)
//    {
//        EHO_splitPipeOffset.append(EHO_eachSplitComma.split("|")[0].toDouble());
//        EHO_splitPipeColumn.append(EHO_eachSplitComma.split("|")[1].toInt());
//    }

//    for (int temp = 0; temp < EHO_splitPipeColumn.size(); temp++)
//    {
//        hitObjectListappend(
//            HitObject(EHO_splitPipeOffset[temp], EHO_splitPipeColumn[temp], newKeys));
//    }
}

// SETTERS
void HitObjectList_impl::setOffsetList(const QList<Offset>& newOffsetList)
{
    AmberException::assertLengthMatch(hitObjectList.length(), newOffsetList.length());

    for (int i = 0; i < newOffsetList.length(); i++)
    {
        hitObjectList[i].setOffset(newOffsetList[i]);
    }

    return;
}
void HitObjectList_impl::setXAxisList(const QList<XAxis>& newXAxisList)
{
    AmberException::assertLengthMatch(hitObjectList.length(), newXAxisList.length());

    for (int i = 0; i < newXAxisList.length(); i++)
    {
        hitObjectList[i].setColumn(newXAxisList[i]);
    }

    return;
}
void HitObjectList_impl::setColumnList(const QList<Column>& newColumnList)
{
    AmberException::assertLengthMatch(hitObjectList.length(), newColumnList.length());

    for (int i = 0; i < newColumnList.length(); i++)
    {
        hitObjectList[i].setColumn(newColumnList[i]);
    }

    return;
}
void HitObjectList_impl::setKeys(const Keys& newKeys)
{
    for (int temp = 0; temp < hitObjectList.length(); temp++)
    {
        hitObjectList[temp].setKeys(newKeys);
    }
}

// GETTERS
QList<Offset> HitObjectList_impl::getOffsetList() const
{
    HitObject OM_HO;
    QList<Offset> output;
    foreach (OM_HO, hitObjectList)
    {
        output.append(OM_HO.getOffset());
    }

    return output;
}
QList<Offset> HitObjectList_impl::getUnqOffsetList() const
{
    QList<Offset> unqOffsetList, offsetList;

    Offset offset;

    offsetList = getOffsetList();

    foreach (offset, offsetList)
    {
        if (!unqOffsetList.contains(offset))
        {
            unqOffsetList.append(offset);
        }
    }

    return offsetList;
}
QList<XAxis> HitObjectList_impl::getXAxisList() const
{
    HitObject OM_HO;
    QList<XAxis> output;
    foreach (OM_HO, hitObjectList)
    {
        output.append(OM_HO.getXAxis());
    }

    return output;
}
QList<Column> HitObjectList_impl::getColumnList() const
{
    HitObject OM_HO;
    QList<Column> output;
    foreach (OM_HO, hitObjectList)
    {
        output.append(OM_HO.getColumn());
    }

    return output;
}
Offset HitObjectList_impl::getMinOffset() const
{
    Offset output;
    QList<Offset> offsetList;
    offsetList = getOffsetList();
    output = *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
Offset HitObjectList_impl::getMaxOffset() const
{
    Offset output;
    QList<Offset> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end());
    return output;
}
Offset HitObjectList_impl::getLength() const
{
    Offset output;
    QList<Offset> offsetList;
    offsetList = getOffsetList();
    output = *std::max_element(offsetList.begin(), offsetList.end())
           - *std::min_element(offsetList.begin(), offsetList.end());
    return output;
}
Offset HitObjectList_impl::getLength(const int& index)
{
    sortOffset(true);

    if (index >= getSize())
    {
        AmberException();
    }
    return Offset(hitObjectList[index + 1].getOffset() -
           hitObjectList[index].getOffset());
}
int HitObjectList_impl::getSize() const
{
    return hitObjectList.count();
}
QStringList HitObjectList_impl::toString() const
{
    HitObject temp;
    QStringList output;

    foreach (temp, hitObjectList)
    {
        output.append(temp.toString());
    }

    return output;
}

// OPERS
HitObject& HitObjectList_impl::operator[](int i)
{
    if (i >= getSize())
    {
        AmberException(AmberException::INDEX_OUT_OF_RANGE, QString("Within HitObjectList_impl\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return *(new HitObject());
    }
    return hitObjectList[i];
}
HitObject HitObjectList_impl::operator[](int i) const
{
    if (i >= getSize())
    {
        AmberException(AmberException::INDEX_OUT_OF_RANGE, QString("Within HitObjectList_impl\n"
                                               "Access: %1\n"
                                               "Last i: %2")
                                           .arg(i)
                                           .arg(getSize() - 1));
        return HitObject();
    }
    return hitObjectList[i];
}

// MISC
void HitObjectList_impl::addColumn(const Column &rhsInt)
{
    QList<Column> newColumnList, oldColumnList;
    Column temp;

    oldColumnList = getColumnList();

    foreach (temp, oldColumnList)
    {
        newColumnList.append(temp + rhsInt);
    }

    setColumnList(newColumnList);
}
void HitObjectList_impl::subtractColumn(const Column& rhsInt)
{
    QList<Column> newColumnList, oldColumnList;
    Column temp;

    oldColumnList = getColumnList();

    foreach (temp, oldColumnList)
    {
        newColumnList.append(temp - rhsInt);
    }

    setColumnList(newColumnList);
}

void HitObjectList_impl::multiplyOffset(const double& rhsDouble)
{
    QList<Offset> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp * rhsDouble);
    }

    setOffsetList(newOffsetList);
}
void HitObjectList_impl::divideOffset(const double& rhsDouble)
{
    QList<Offset> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp / rhsDouble);
    }

    setOffsetList(newOffsetList);
}
void HitObjectList_impl::addOffset(const double& rhsDouble)
{
    QList<Offset> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp + rhsDouble);
    }

    setOffsetList(newOffsetList);
}
void HitObjectList_impl::subtractOffset(const double& rhsDouble)
{
    QList<Offset> newOffsetList, oldOffsetList;
    int temp;

    oldOffsetList = this->getOffsetList();

    foreach (temp, oldOffsetList)
    {
        newOffsetList.append(temp - rhsDouble);
    }

    setOffsetList(newOffsetList);
}

void HitObjectList_impl::makeUnique()
{
    QList<Offset> offsetList, newOffsetList;
    QList<HitObject> newHOList;

    offsetList = getOffsetList();

    for (int temp = 0; temp < offsetList.length(); temp++)
    {
        if (!newOffsetList.contains(offsetList[temp]))
        {
            newOffsetList.append(offsetList[temp]);
            newHOList.append(HitObject(
                offsetList[temp], hitObjectList[temp].getColumn(), hitObjectList[temp].getKeys()));
        }
    }

    loadHOList(newHOList);
}
void HitObjectList_impl::sortOffset(const bool& isAscending)
{
    if (isAscending)
    {
        std::sort(hitObjectList.begin(), hitObjectList.end(), [](const HitObject &left, const HitObject &right)
        {
            return left.getOffset() < right.getOffset();
        });
    }
    else
    {
        std::sort(hitObjectList.begin(), hitObjectList.end(), [](const HitObject &left, const HitObject &right)
        {
            return left.getOffset() < right.getOffset();
        });
    }
}

bool HitObjectList_impl::isEmpty() const
{
    return (getSize() == 0);
}

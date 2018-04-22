#include "com_breakp.h"

// CONSTRUCTORS
cOM_BreakP::cOM_BreakP()
{
    startBreak = 0;
    endBreak   = 1;
}
cOM_BreakP::cOM_BreakP(QString newBreakP) : cOM_BreakP()
{
    loadBreakP(newBreakP);
}

// LOADERS
void cOM_BreakP::loadBreakP(QString newBreakP)
{
    QStringList BreakPList;

    BreakPList = newBreakP.split(",", QString::KeepEmptyParts);

    if (BreakPList.count() != 3) {
        ER_DEBUG("Break Period Invalid");
        ER_DEBUG("Input: " + newBreakP);
        cOM_BreakP();
    }

    startBreak = BreakPList[1].toDouble();
    endBreak   = BreakPList[2].toDouble();
}

// SETTERS

// GETTERS
void cOM_BreakP::getInfo() const
{
    INF_DEBUG("[---- Break Info ----]"    );
    INF_DEBUG("STARTBREAK : " + QString::number(startBreak));
    INF_DEBUG("ENDBREAK   : " + QString::number(endBreak  ));
}

// OPERS

// SORTING

// MISC






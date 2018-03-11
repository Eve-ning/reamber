#include "com_holist.h"

cOM_HOList::cOM_HOList()
{

}

cOM_HOList::cOM_HOList(cOM_HO newOM_HOList[])
{
    OM_HOList = newOM_HOList;
    size = sizeof(newOM_HOList);
}

QList<double> cOM_HOList::getOffsetList()
{
    cOM_HO OM_HO;
    QList<double> output;
    foreach (OM_HO, OM_HOList)
    {
        output.append(OM_HO.getOffset());
    }
}

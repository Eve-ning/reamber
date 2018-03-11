#ifndef COM_HOLIST_H
#define COM_HOLIST_H
#include "com_ho.h"

class cOM_HOList
{
public:
    cOM_HOList();
    cOM_HOList(cOM_HO newOM_HOList[]); // Initialize via array of OM_HO
    cOM_HOList(QString EHO);    // Initialize via EHO and convert all to OM_HO

    unsigned long   operator [](int i) const { return OM_HO[i]; }
    unsigned long & operator [](int i)       { return OM_HO[i]; }

    QList<double> getOffsetList();
    QList<double> getCodeList();
    QList<double> getColumnList();

    double getMinOffset();
    double getMaxOffset();
    double getLength   ();


    void append     (cOM_HO newOM_HO);
    void deleteIndex(unsigned  index);


private:

    unsigned size;
    cOM_HO   OM_HOList[];
};

#endif // COM_HOLIST_H

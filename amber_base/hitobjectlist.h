#ifndef HitObjectLIST_H
#define HitObjectLIST_H

#include "amber_base/common.h"
#include "amber_base/obj_impl/hitobjectlist_impl.h"


class HitObjectList : public HitObjectList_impl
{
public:
    // CONSTRUCTORS
    HitObjectList();
    HitObjectList(QList<HitObject> newHOList);
    HitObjectList(QString        EHO    , int newKeys = 0);
    HitObjectList(QTextBrowser   *tb    , int newKeys = 0);
    HitObjectList(QLineEdit      *line  , int newKeys = 0);
    HitObjectList(QPlainTextEdit *pte   , int newKeys = 0);
    HitObjectList(QStringList    strList, int newKeys = 0);

};

#endif // HitObjectLIST_H

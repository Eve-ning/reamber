#include "amber_base/hitobjectlist.h"

// CONSTRUCTORS
HitObjectList::HitObjectList() : HitObjectList_impl()
{
}
HitObjectList::HitObjectList(QList<HitObject> newHOList)
    : HitObjectList()
{
    loadHOList(newHOList);
}
HitObjectList::HitObjectList(QString EHO, int newKeys)
    : HitObjectList()
{
    loadHOList(EHO, newKeys);
}
HitObjectList::HitObjectList(QTextBrowser* tb, int newKeys)
    : HitObjectList()
{
    loadHOList(tb, newKeys);
}
HitObjectList::HitObjectList(QLineEdit* line, int newKeys)
    : HitObjectList()
{
    loadHOList(line, newKeys);
}
HitObjectList::HitObjectList(QPlainTextEdit* pte, int newKeys)
    : HitObjectList()
{
    loadHOList(pte, newKeys);
}



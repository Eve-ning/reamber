#include "amber_base/hitobject.h"

// CONSTRUCTORS
HitObject::HitObject():
    HitObject_impl()
{

}
HitObject::HitObject(const Offset &newOffset,
                     const Column &newColumn,
                     const Keys &newKeys)
    : HitObject()
{
    loadHO(newOffset, newColumn, newKeys);
}
HitObject::HitObject(const QLineEdit* line,
                     const Keys &newKeys)
    : HitObject()
{
    loadHO(line, newKeys);
}
HitObject::HitObject(const QString& HO,
                     const Keys &newKeys)
    : HitObject()
{
    loadHO(HO, newKeys);
}



// MISC

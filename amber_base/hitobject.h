#ifndef COM_HO_H
#define COM_HO_H

#include "amber_base/obj_impl/hitobject_impl.h"

class HitObject : public HitObject_impl
{
public:

    // CONSTRUCTORS
    HitObject();
    HitObject(const QString &HO, const Keys &newKeys = 0);
    HitObject(const Offset &newOffset, const Column &newColumn, const Keys &newKeys = 0);
    HitObject(const QLineEdit *line, const Keys &newKeys = 0);

};

#endif // COM_HO_H

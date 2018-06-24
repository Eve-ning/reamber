#ifndef VALIDOBJ_HPP
#define VALIDOBJ_HPP
#include <QString>
#include "amber_base/validity/amberexception.h"

namespace ValidObj
{
bool hitObject(const QString &value_); // EHO returns true here too
bool hitObject(const QStringList &value_); // EHO returns true here too
bool editorHitObject(const QString &value_);
bool timingPoint(const QString &value_);
bool timingPoint(const QStringList &value_);

bool assertHitObject(const QString &value_);
bool assertHitObject(const QStringList &value_);
bool assertTimingPoint(const QString &value_);
bool assertTimingPoint(const QStringList &value_);
const int HITOBJECT_COMMA = 5;
const int HITOBJECTNN_COLON = 4;
const int HITOBJECTLN_COLON = 5;
const int TIMINGPOINT_COMMA = 7;

/* REFERENCE
 *
 * NORMAL NOTE
 * 448,192,1000,1,0,0:0:0:0:
 *
 * LONG NOTE
 * 448,192,1000,128,0,2000:0:0:0:0:
 *
 * SLIDER VELOCITY
 * 1000,-100,4,3,0,20,0,0
 *
 * BPM
 * 1000,60000,4,2,0,100,1,0
 */

}

#endif // VALIDOBJ_H

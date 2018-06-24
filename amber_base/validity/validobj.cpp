#include "amber_base/validity/validobj.h"

bool ValidObj::hitObject(const QString &value_)
{
    if (value_.indexOf(',') > -1)
        //.osu case
    {
        int comma = std::count(value_.begin(),value_.end(),',');
        int colon = std::count(value_.begin(),value_.end(),':');

        return ((comma == ValidObj::HITOBJECT_COMMA) &&
                (colon == ValidObj::HITOBJECTNN_COLON || colon == ValidObj::HITOBJECTLN_COLON));
    }
    else if (value_.indexOf('-') > -1)
        // editor case
    {
        return editorHitObject(value_);
    }
    return false;
}
bool ValidObj::timingPoint(const QString &value_)
{
    int comma = std::count(value_.begin(),value_.end(),',');

    return (comma == ValidObj::TIMINGPOINT_COMMA);
}
bool ValidObj::editorHitObject(const QString &value_)
{
    if (value_.indexOf('(') > -1 &&
        value_.indexOf(')') > -1 &&
        value_.indexOf('|') > -1)
    {
        return true;
    }
    return false;
}

bool ValidObj::hitObject(const QStringList &value_)
{
    for (int i = 0; i < value_.length(); i ++)
    {
        if (!hitObject(value_[i]))
        {
            return false;
        }
    }
    return true;
}
bool ValidObj::timingPoint(const QStringList &value_)
{
    for (int i = 0; i < value_.length(); i ++)
    {
        if (!timingPoint(value_[i]))
        {
            return false;
        }
    }
    return true;
}

bool ValidObj::assertHitObject(const QString &value_)
{
    if (!hitObject(value_))
    {
        AmberException(AmberException::HO_LOADFAIL, value_);
        return false;
    }
    return true;
}
bool ValidObj::assertTimingPoint(const QString &value_)
{
    if (!timingPoint(value_))
    {
        AmberException(AmberException::TP_LOADFAIL, value_);
        return false;
    }
    return true;
}
bool ValidObj::assertHitObject(const QStringList &value_)
{
    if (!hitObject(value_))
    {
        AmberException(AmberException::HO_LOADFAIL, value_.join('\n'));
        return false;
    }
    return true;
}
bool ValidObj::assertTimingPoint(const QStringList &value_)
{
    if (!timingPoint(value_))
    {
        AmberException(AmberException::TP_LOADFAIL, value_.join('\n'));
        return false;
    }
    return true;
}
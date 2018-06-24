#ifndef HITSOUNDFILE_H
#define HITSOUNDFILE_H
#include "amber_base/parameters/base_/amberstring.h"
#include <QFile>

class HitsoundFile : public AmberString
{
public:
    HitsoundFile() : AmberString(""){
    }

    HitsoundFile(const QString &value) : AmberString(""){
        m_string = value;
    }
};

#endif // HITSOUNDFILE_H

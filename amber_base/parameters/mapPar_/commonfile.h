#ifndef COMMONFILE_H
#define COMMONFILE_H
#include "amber_base/parameters/base_/amberstring.h"
#include <QFile>

class CommonFile : public AmberString
{
public:
    CommonFile() : AmberString(""){
    }

    CommonFile(const QString &string) : AmberString(""){
        m_string = string;
    }

    CommonFile(const char array[] ){
        m_string = QString(array);
    }
};

#endif // COMMONFILE_H

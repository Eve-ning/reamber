#include "amberstring.h"

QString AmberString::string() const
{
    return m_string;
}

void AmberString::setString(const QString &string)
{
    m_string = string;
}

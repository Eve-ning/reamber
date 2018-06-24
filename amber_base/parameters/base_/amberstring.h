#ifndef AMBERSTRING_H
#define AMBERSTRING_H
#include <QtCore>

class AmberString
{
public:
    AmberString(const QString &string = "") {
        m_string = string;
    }

    // append alias
    AmberString operator +(const AmberString &string) const {
        AmberString temp = *this;
        temp.append(string);
        return temp;
    }
    AmberString operator +(const QString &string) const {
        AmberString temp = *this;
        temp.append(string);
        return temp;
    }
    // chop alias
    AmberString operator -(int value) const {
        AmberString temp = *this;
        temp.chop(value);
        return temp;
    }
    AmberString operator =(const QString &string){
        m_string = string;
        return *this;
    }

    // append alias
    void operator +=(const AmberString &value){ this->append(value); }
    void operator +=(const QString &value){ this->append(value); }
    // chop alias
    void operator -=(int value){ this->chop(value); }

    void append(const AmberString &value){
        m_string.append(value.string());
    }
    void append(const QString &value){
        m_string.append(value);
    }
    void chop(int value){
        m_string.chop(value);
    }
    int length() const {
        return m_string.length();
    }

    // length comparison
    bool operator > (const AmberString &value) const { return m_string.length() >  value.string().length(); }
    bool operator >=(const AmberString &value) const { return m_string.length() >= value.string().length(); }
    bool operator < (const AmberString &value) const { return m_string.length() <  value.string().length(); }
    bool operator <=(const AmberString &value) const { return m_string.length() <= value.string().length(); }

    // content match comparison
    bool operator ==(const AmberString &value) const { return m_string == value.string(); }
    bool operator !=(const AmberString &value) const { return m_string != value.string(); }

    QString toString() const {
        return QString(m_string);
    }
    operator QString() const {
        return toString();
    }

    QString string() const;
    void setString(const QString &string);

protected:
    QString m_string;
};

#endif // AMBERSTRING_H

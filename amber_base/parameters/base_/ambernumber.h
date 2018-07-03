#ifndef BASE_N_H
#define BASE_N_H
#include <QtCore>

class AmberNumber
{
public:
    AmberNumber(double value,
                bool forceInt = false,
                double clampMin = INT_MIN,
                double clampMax = INT_MAX)
    {
        m_value = value;
        m_forceInt = forceInt;
        m_clampMin = clampMin;
        m_clampMax = clampMax;
    }

    AmberNumber(int value,
                bool forceInt = true,
                double clampMin = INT_MIN,
                double clampMax = INT_MAX)
    {
        m_value = value;
        m_forceInt = forceInt;
        m_clampMin = clampMin;
        m_clampMax = clampMax;
    }

    virtual ~AmberNumber(){}

    operator double() const {
        return value();
    }
    operator int() const {
        return floor(value());
    }
    virtual operator QString() const {
        return QString::number(m_value);
    }
    void operator =(const AmberNumber &value){
        setValue(value);
    }
    void operator =(const double &value){
        setValue(value);
    }
    void operator =(const int &value){
        setValue(value);
        m_forceInt = true;
    }

    void setValue(const double &value){
        m_value = value;
        clamp();
        floorVal();
    }
    void setValue(const AmberNumber &value){
        m_value = value.value();
        // We reclamp and refloor according to THIS object's settings
        clamp();
        floorVal();
    }

    void setClampMin(const double &value){
        m_clampMin = value;
        clamp(); // Reclamp on change of limits
    }
    void setClampMax(const double &value){
        m_clampMax = value;
        clamp(); // Reclamp on change of limits
    }
    void setClamps(const double &clampMin,
                   const double &clampMax){
        m_clampMin = clampMin;
        m_clampMax = clampMax;
        clamp(); // Reclamp on change of limits
    }

    double value() const{
        return m_value;
    }

    AmberNumber operator +(const AmberNumber &value) const { return m_value + value.value(); }
    AmberNumber operator -(const AmberNumber &value) const { return m_value - value.value(); }
    AmberNumber operator *(const AmberNumber &value) const { return m_value * value.value(); }
    AmberNumber operator /(const AmberNumber &value) const { return m_value / value.value(); }

    AmberNumber operator +(const double &value) const { return m_value + value; }
    AmberNumber operator -(const double &value) const { return m_value - value; }
    AmberNumber operator *(const double &value) const { return m_value * value; }
    AmberNumber operator /(const double &value) const { return m_value / value; }

    void operator +=(const AmberNumber &value){ setValue(m_value + value.value());}
    void operator -=(const AmberNumber &value){ setValue(m_value - value.value());}
    void operator *=(const AmberNumber &value){ setValue(m_value * value.value());}
    void operator /=(const AmberNumber &value){ setValue(m_value / value.value());}

    void operator +=(const double &value){ setValue(m_value + value);}
    void operator -=(const double &value){ setValue(m_value - value);}
    void operator *=(const double &value){ setValue(m_value * value);}
    void operator /=(const double &value){ setValue(m_value / value);}

    bool operator > (const AmberNumber &value) const { return m_value >  value.value(); }
    bool operator >=(const AmberNumber &value) const { return m_value >= value.value(); }
    bool operator < (const AmberNumber &value) const { return m_value <  value.value(); }
    bool operator <=(const AmberNumber &value) const { return m_value <= value.value(); }

    bool operator ==(const AmberNumber &value) const { return m_value == value.value(); }
    bool operator !=(const AmberNumber &value) const { return m_value != value.value(); }

    bool operator > (const double &value) const { return m_value >  value; }
    bool operator >=(const double &value) const { return m_value >= value; }
    bool operator < (const double &value) const { return m_value <  value; }
    bool operator <=(const double &value) const { return m_value <= value; }

    bool operator ==(const double &value) const { return m_value == value; }
    bool operator !=(const double &value) const { return m_value != value; }

protected:

    double m_value;
    double m_clampMin;
    double m_clampMax;
    bool m_forceInt;

private:

    void clamp();
    void floorVal();
};

#endif // BASE_N_H

#ifndef METRONOME_H
#define METRONOME_H
#include "amber_base/parameters/base_/ambernumber.h"

class Metronome : public AmberNumber
{
public:
    Metronome() : AmberNumber(4, true, 1, INT_MAX){
    }

    Metronome(const int &value) : AmberNumber(4, true, 1, INT_MAX){
        m_value = value;
    }

    Metronome(AmberNumber value) : AmberNumber(4, true, 1, INT_MAX){
        m_value = value;
    }
};

#endif // METRONOME_H

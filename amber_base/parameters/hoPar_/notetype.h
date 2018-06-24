#ifndef NOTETYPE_H
#define NOTETYPE_H
#include "amber_base/parameters/base_/ambernumber.h"

class NoteType : public AmberNumber
{
public:

    enum NOTE_TYPE {
        NORMAL_NOTE = 1,
        INIT_NOTE = 5, // Represents the very first note of the chart (As a normal note)
        LONG_NOTE = 128
    };

    NoteType() : AmberNumber(1, true, 1, 128){
    }

    NoteType(NOTE_TYPE value) : AmberNumber(1, true, 1, 128){
        m_value = (int)value;
    }

    // We don't have a int/double setValue as there are invalid numbers in between the clamps

    bool isNormalNote() const {
        return (m_value == NOTE_TYPE::NORMAL_NOTE ||
                m_value == NOTE_TYPE::INIT_NOTE);
    }
    bool isLongNote() const {
        return (m_value == NOTE_TYPE::LONG_NOTE);
    }

    using AmberNumber::setValue;
    void setValue(const NOTE_TYPE &value) {
        m_value = (int)value;
    }

};

#endif // NOTETYPE_H

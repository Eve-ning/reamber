#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "amber_base/parameters/base_/ambernumber.h"

class GameMode : public AmberNumber
{
public:

    enum GAME_MODE{
        STANDARD = 0,
        TAIKO    = 1,
        CTB      = 2,
        MANIA    = 3
    };

    GameMode() : AmberNumber(0, true, 0, 3){
    }

    GameMode(const GAME_MODE &value) : AmberNumber(0, true, 0, 3){
        m_value = int(value);
    }

    GameMode(int value) : AmberNumber(0, true, 0, 3){
        m_value = value;
    }

    using AmberNumber::setValue;
    void setValue(const GAME_MODE &value) {
        m_value = (int)value;
    }

    bool isSTANDARD(){
        return (m_value == (int)GAME_MODE::STANDARD);
    }
    bool isTAIKO(){
        return (m_value == (int)GAME_MODE::TAIKO);
    }
    bool isCTB(){
        return (m_value == (int)GAME_MODE::CTB);
    }
    bool isMANIA(){
        return (m_value == (int)GAME_MODE::MANIA);
    }

};

#endif // GAMEMODE_H

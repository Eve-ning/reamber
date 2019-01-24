#include "info.h"

Info::Info()
{
    isHO     = false;
    isTP     = false;
    isEHO    = false;
    isSV     = false;
    isBPM    = false;
    isNN     = false;
    isLN     = false;
    loadFail = false;
}
Info::Info(const bool &allCondition)
{
    isHO     = allCondition;
    isTP     = allCondition;
    isEHO    = allCondition;
    isSV     = allCondition;
    isBPM    = allCondition;
    isNN     = allCondition;
    isLN     = allCondition;
    loadFail = false;
}
Info::Info(const int newCondition)
{
    setCondition(newCondition);
}

QString Info::toString(const bool &type) const
{
    QString output;

    if (type)
    {
        if (isHO    ){ output.append("isHO"    ); }
        if (isTP    ){ output.append("isTP"    ); }
        if (isEHO   ){ output.append("isEHO"   ); }
        if (isSV    ){ output.append("isSV"    ); }
        if (isBPM   ){ output.append("isBPM"   ); }
        if (isNN    ){ output.append("isNN"    ); }
        if (isLN    ){ output.append("isLN"    ); }
        if (loadFail){ output.append("loadFail"); }
    }
    else
    {
        if (!isHO    ){ output.append("isHO"    ); }
        if (!isTP    ){ output.append("isTP"    ); }
        if (!isEHO   ){ output.append("isEHO"   ); }
        if (!isSV    ){ output.append("isSV"    ); }
        if (!isBPM   ){ output.append("isBPM"   ); }
        if (!isNN    ){ output.append("isNN"    ); }
        if (!isLN    ){ output.append("isLN"    ); }
        if (!loadFail){ output.append("loadFail"); }
    }
    return output;
}

int Info::getCondition()
{
    int condition = 0x0;

    if (getIsHO    ()) { condition = condition | IS_HO   ; }
    if (getIsTP    ()) { condition = condition | IS_TP   ; }
    if (getIsEHO   ()) { condition = condition | IS_EHO  ; }
    if (getIsSV    ()) { condition = condition | IS_SV   ; }
    if (getIsBPM   ()) { condition = condition | IS_BPM  ; }
    if (getIsNN    ()) { condition = condition | IS_NN   ; }
    if (getIsLN    ()) { condition = condition | IS_LN   ; }
    if (getLoadFail()) { condition = condition | LOADFAIL; }

    return condition;
}
void Info::appendCondition(int newCondition)
{
    setCondition(getCondition() | newCondition);
}
void Info::setCondition(int newCondition)
{
    if ((newCondition & IS_HO) == IS_HO) {
      setIsHO(true);
    } else {
      setIsHO(false);
    }
    if ((newCondition & IS_TP) == IS_TP) {
      setIsTP(true);
    } else {
      setIsTP(false);
    }
    if ((newCondition & IS_EHO) == IS_EHO) {
      setIsEHO(true);
    } else {
      setIsEHO(false);
    }
    if ((newCondition & IS_SV) == IS_SV) {
      setIsSV(true);
    } else {
      setIsSV(false);
    }
    if ((newCondition & IS_BPM) == IS_BPM) {
      setIsBPM(true);
    } else {
      setIsBPM(false);
    }
    if ((newCondition & IS_NN) == IS_NN) {
      setIsNN(true);
    } else {
      setIsNN(false);
    }
    if ((newCondition & IS_LN) == IS_LN) {
      setIsLN(true);
    } else {
      setIsLN(false);
    }
    if ((newCondition & LOADFAIL) == LOADFAIL) {
      setLoadFail(true);
    } else {
      setLoadFail(false);
    }
}

void Info::setIsHO(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    isNN = value; // We set NN & LN & EHO as according to the value as HO is the super
    isLN = value;
    isEHO = value;

    isHO = value;
}
void Info::setIsTP(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    isSV  = value; // We set SV & BPM as according to the value as TP is the super
    isBPM = value;

    isTP = value;
}
void Info::setIsEHO(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isHO = true; // EHO is a HO
    }

    isEHO = value;

    if (!(isEHO || isNN || isLN)) // If all of them are false we disable isHO
    {
        isHO = false;
    }
}
void Info::setIsSV(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isTP = true; // SV is a TP
    }

    isSV = value;

    if (!(isSV || isBPM)) // If both are false, we disable isTP
    {
        isTP = false;
    }
}
void Info::setIsBPM(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isTP = true; // BPM is a TP
    }

    isBPM = value;

    if (!(isSV || isBPM)) // If both are false, we disable isTP
    {
        isTP = false;
    }
}
void Info::setIsNN(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isHO = true; // NN is a HO
    }

    isNN = value;

    if (!(isEHO || isNN || isLN)) // If all of them are false we disable isHO
    {
        isHO = false;
    }
}
void Info::setIsLN(bool value)
{
    if (getLoadFail()) { return; } // Cannot change value when input is bad
    if (value)
    {
        isHO = true; // LN is a HO
    }

    isLN = value;

    if (!(isEHO || isNN || isLN)) // If all of them are false we disable isHO
    {
        isHO = false;
    }
}
void Info::setLoadFail(bool value)
{
    // On load fail, all other values will be set to false
    loadFail = value;
    if (loadFail)
    {
        isHO   = false;
        isTP   = false;
        isEHO  = false;
        isSV   = false;
        isBPM  = false;
        isNN   = false;
        isLN   = false;
    }
}

QStringList Info::getAllTrue() const
{
    QStringList output;
    if(isHO    ){ output.append("isHO\t"    ); }
    if(isTP    ){ output.append("isTP\t"    ); }
    if(isEHO   ){ output.append("isEHO\t"   ); }
    if(isSV    ){ output.append("isSV\t"    ); }
    if(isBPM   ){ output.append("isBPM\t"   ); }
    if(isNN    ){ output.append("isNN\t"    ); }
    if(isLN    ){ output.append("isLN\t"    ); }
    if(loadFail){ output.append("loadFail\t"); }

    return output;
}
QStringList Info::getAllFalse() const
{
    QStringList output;
    if(!isHO    ){ output.append("isHO\t"    ); }
    if(!isTP    ){ output.append("isTP\t"    ); }
    if(!isEHO   ){ output.append("isEHO\t"   ); }
    if(!isSV    ){ output.append("isSV\t"    ); }
    if(!isBPM   ){ output.append("isBPM\t"   ); }
    if(!isNN    ){ output.append("isNN\t"    ); }
    if(!isLN    ){ output.append("isLN\t"    ); }
    if(!loadFail){ output.append("loadFail\t"); }

    return output;
}

QString Info::getFailMsg() const
{
    return failMsg;
}
void Info::setFailMsg(const QString value)
{
    failMsg = value;
}

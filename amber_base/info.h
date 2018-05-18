#ifndef INFO_H
#define INFO_H
#include "aexc.h"

class Info
{
public:

    Info();
    Info(const bool &allCondition);
    Info(const int  newCondition); // We use Hexadecimal to set this

    QString toString(const bool &type) const;

    bool getIsHO    () const { return isHO    ; }
    bool getIsTP    () const { return isTP    ; }
    bool getIsEHO   () const { return isEHO   ; }
    bool getIsSV    () const { return isSV    ; }
    bool getIsBPM   () const { return isBPM   ; }
    bool getIsNN    () const { return isNN    ; }
    bool getIsLN    () const { return isLN    ; }
    bool getLoadFail() const { return loadFail; }

    static const int IS_HO    = 0x01;
    static const int IS_TP    = 0x02;
    static const int IS_EHO   = 0x04;
    static const int IS_SV    = 0x08;
    static const int IS_BPM   = 0x10;
    static const int IS_NN    = 0x20;
    static const int IS_LN    = 0x40;
    static const int LOADFAIL = 0x80;

    void setCondition(int newCondition);
    int  getCondition();
    void appendCondition(int newCondition);

    void setIsHO    (bool value);
    void setIsTP    (bool value);
    void setIsEHO   (bool value);
    void setIsSV    (bool value);
    void setIsBPM   (bool value);
    void setIsNN    (bool value);
    void setIsLN    (bool value);
    void setLoadFail(bool value);

    QString getFailMsg() const;
    void    setFailMsg(const QString value);

    QStringList getAllTrue() const;
    QStringList getAllFalse() const;

private:

    bool
    isHO, isTP, isEHO,
    isSV, isBPM,
    isNN, isLN,
    loadFail; // Failed to load completely
    QString failMsg;
};


#endif // INFO_H

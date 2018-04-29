#ifndef COM_COMMON_H
#define COM_COMMON_H
#include <QtCore>
#include <QtWidgets>

class omInfo
{
public:

    omInfo();
    omInfo(const bool &allCondition);

    QString toString(const bool &type) const;

    bool getIsHO    () const;
    bool getIsTP    () const;
    bool getIsEHO   () const;
    bool getIsSV    () const;
    bool getIsBPM   () const;
    bool getIsNN    () const;
    bool getIsLN    () const;
    bool getLoadFail() const;

    void setIsHO    (bool value);
    void setIsTP    (bool value);
    void setIsEHO   (bool value);
    void setIsSV    (bool value);
    void setIsBPM   (bool value);
    void setIsNN    (bool value);
    void setIsLN    (bool value);
    void setLoadFail(bool value);

    QString getFailMsg() const;
    void setFailMsg(const QString value);

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

class cOM_Common
{
public:
    cOM_Common();

    static omInfo whatHO(const QTextBrowser   *tb)    ;
    static omInfo whatHO(const QLineEdit      *line)  ;
    static omInfo whatHO(const QPlainTextEdit *pte)   ;
    static omInfo whatHO(const QString        &HO)    ;
    static omInfo whatHO(const QStringList    &HOList); // FUNNEL TARGET

    static omInfo whatTP(const QTextBrowser   *tb)    ;
    static omInfo whatTP(const QLineEdit      *line)  ;
    static omInfo whatTP(const QPlainTextEdit *pte)   ;
    static omInfo whatTP(const QString        &TP)    ;
    static omInfo whatTP(const QStringList    &TPList); // FUNNEL TARGET

    // isOM_Type checks both TP and OM
    static omInfo whatOM_Type(const QTextBrowser   *tb)   ;
    static omInfo whatOM_Type(const QLineEdit      *line) ;
    static omInfo whatOM_Type(const QPlainTextEdit *pte)  ;
    static omInfo whatOM_Type(const QString        &input);
    static omInfo whatOM_Type(const QStringList    &input); // FUNNEL TARGET

    static bool isHO(const QTextBrowser   *tb)    ;
    static bool isHO(const QLineEdit      *line)  ;
    static bool isHO(const QPlainTextEdit *pte)   ;
    static bool isHO(const QString        &HO)    ;
    static bool isHO(const QStringList    &HOList); // FUNNEL TARGET

    static bool isTP(const QTextBrowser   *tb)    ;
    static bool isTP(const QLineEdit      *line)  ;
    static bool isTP(const QPlainTextEdit *pte)   ;
    static bool isTP(const QString        &HO)    ;
    static bool isTP(const QStringList    &HOList); // FUNNEL TARGET

    static bool isEHO(const QTextBrowser   *tb)    ;
    static bool isEHO(const QLineEdit      *line)  ;
    static bool isEHO(const QPlainTextEdit *pte)   ;
    static bool isEHO(const QString        &HO)    ;
    static bool isEHO(const QStringList    &HOList); // FUNNEL TARGET

    static void assertHO(const QTextBrowser   *tb)    ;
    static void assertHO(const QLineEdit      *line)  ;
    static void assertHO(const QPlainTextEdit *pte)   ;
    static void assertHO(const QString        &HO)    ;
    static void assertHO(const QStringList    &HOList); // FUNNEL TARGET

    static void assertTP(const QTextBrowser   *tb)    ;
    static void assertTP(const QLineEdit      *line)  ;
    static void assertTP(const QPlainTextEdit *pte)   ;
    static void assertTP(const QString        &HO)    ;
    static void assertTP(const QStringList    &HOList); // FUNNEL TARGET

    static void assertIndex        (const int &value, const int &max);
    static void assertEmpty        (const QList<class T> &value, const QString &funcName);
    static void assertEmpty        (const QStringList &value, const QString &funcName);
    static void assertDivByZero    (const double &value);
    static void assertOffsetValid  (const int &newOffset);  // Checks w.r.t. specified offset
    static void assertLengthMatch  (const int &given, const int &expected);
    static void assertInvalidFormat(const QString &value);
    static void assertLoadFail     (const omInfo &info);

    static constexpr double MINIMUM_OFFSET = 0;
    static constexpr double MAXIMUM_OFFSET = 360000;

};

class amberException
{
public:
    amberException()
    {
        msg = "";
    }
    amberException(const QString newMsg)
    {
        msg = newMsg;
    }
    QString msg;
};

class columnOutOfRange : public amberException
{
public:
    columnOutOfRange(const double newValue, const double min, const double max);

    QString excName = "columnOutOfRange";
    QString what = "Occurs when set column goes out of range w.r.t. the key or fixed range [0 - 17]";
    double badValue;
};
class offsetOutOfRange : public amberException
{
public:
    offsetOutOfRange(const double newValue, const double min, const double max);

    QString excName = "offsetOutOfRange";
    QString what = "Occurs when set offset goes out of range [0 - 360000 <1 HOUR IN MS>]";
    double badValue;
};
class keysOutOfRange : public amberException
{
public:
    keysOutOfRange(const int newValue, const int min, const int max);

    QString excName = "keysOutOfRange";
    QString what = "Occurs when set key goes out of range [1 - 18]";
    int badValue;
};
class xAxisOutOfRange : public amberException
{
public:
    xAxisOutOfRange(const int newValue, const int min, const int max);

    QString excName = "xAxisOutOfRange";
    QString what = "Occurs when set offset goes out of range [0 - 512]";
    int badValue;
};
class emptyException : public amberException
{
public:
    emptyException(const QString objName);

    QString excName = "emptyException";
    QString what = "Occurs when function that requires a non empty class (TPList/HOList) is executed";
};
class TPLoadFail : public amberException
{
public:
    TPLoadFail(const QString     newValue);
    TPLoadFail(const QStringList newValue);

    QString excName = "TPLoadFail";
    QString what = "Failed to load as TP";
    QString badValue;
};
class HOLoadFail : public amberException
{
public:
    HOLoadFail(const QString     newValue);
    HOLoadFail(const QStringList newValue);

    QString excName = "HOLoadFail";
    QString what = "Failed to load as HO";
    QString badValue;
};
class indexOutOfRange : public amberException
{
public:
    indexOutOfRange(const int newValue, const int max);

    QString excName = "indexOutOfRange";
    QString what = "An index used was out of bounds";
    int badValue;
};
class lengthMismatch : public amberException
{
public:
    lengthMismatch(const int givenLength, const int expectedLength);

    QString excName = "lengthMismatch";
    QString what = "Length given didn't match the expected (eg. setting an offset list on HOList requires the same length)";
    int givenValue, expectedValue;
};
class divideByZeroException : public amberException
{
public:

    QString excName = "divideByZeroException";
    QString what = "Attempt to divide by zero";
    divideByZeroException();
};
class loadFailException: public amberException
{
public:
    loadFailException(const omInfo info);

    QString excName = "loadFailException";
    QString what = "Attempt to use functions while loadFail is active";
};

#endif // cOM_Common_H

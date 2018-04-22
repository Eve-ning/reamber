#ifndef COM_COMMON_H
#define COM_COMMON_H
#include <QtCore>
#include <QtWidgets>

class columnOutOfRange
{
public:
    columnOutOfRange(double newValue, double min, double max);

    QString msg;
    double badValue;
};
class offsetOutOfRange
{
public:
    offsetOutOfRange(double newValue, double min, double max);

    QString msg;
    double badValue;
};
class keysOutOfRange
{
public:
    keysOutOfRange(int newValue, int min, int max);

    QString msg;
    int badValue;
};
class xAxisOutOfRange
{
public:
    xAxisOutOfRange(int newValue, int min, int max);

    QString msg;
    int badValue;
};
class emptyException
{
public:
    emptyException(QString objName);

    QString msg;
};

class TPLoadFail
{
public:
    TPLoadFail(QString newValue);
    TPLoadFail(QStringList newValue);

    QString msg;
    QString badValue;
};
class HOLoadFail
{
public:
    HOLoadFail(QString newValue);
    HOLoadFail(QStringList newValue);

    QString msg;
    int badValue;
};

class invalidFormat
{
public:
    invalidFormat(QString &newValue, QString &newFailMsg);
    QString msg;
    QString failMsg;
    QString badValue;
};

class indexOutOfRange
{
public:
    indexOutOfRange(int newValue, int max);

    QString msg;
    int badValue;
};
class lengthMismatch
{
public:
    lengthMismatch(int givenLength, int expectedLength);

    QString msg;
    int givenValue, expectedValue;
};

class divideByZeroException
{
    divideByZeroException()
    {
        msg = "Attempted to divide by Zero";
    }

    QString msg;
};

class omInfo
{
public:

    omInfo();

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

    static void whatHO(omInfo &info, QTextBrowser   *tb)    ;
    static void whatHO(omInfo &info, QLineEdit      *line)  ;
    static void whatHO(omInfo &info, QPlainTextEdit *pte)   ;
    static void whatHO(omInfo &info, QString        &HO)    ;
    static void whatHO(omInfo &info, QStringList    &HOList); // FUNNEL TARGET

    static void whatTP(omInfo &info, QTextBrowser   *tb)    ;
    static void whatTP(omInfo &info, QLineEdit      *line)  ;
    static void whatTP(omInfo &info, QPlainTextEdit *pte)   ;
    static void whatTP(omInfo &info, QString        &TP)    ;
    static void whatTP(omInfo &info, QStringList    &TPList); // FUNNEL TARGET

    static bool isHO(QTextBrowser   *tb)    ;
    static bool isHO(QLineEdit      *line)  ;
    static bool isHO(QPlainTextEdit *pte)   ;
    static bool isHO(QString        &HO)    ;
    static bool isHO(QStringList    &HOList); // FUNNEL TARGET

    static bool isTP(QTextBrowser   *tb)    ;
    static bool isTP(QLineEdit      *line)  ;
    static bool isTP(QPlainTextEdit *pte)   ;
    static bool isTP(QString        &HO)    ;
    static bool isTP(QStringList    &HOList); // FUNNEL TARGET

    static bool isEHO(QTextBrowser   *tb)    ;
    static bool isEHO(QLineEdit      *line)  ;
    static bool isEHO(QPlainTextEdit *pte)   ;
    static bool isEHO(QString        &HO)    ;
    static bool isEHO(QStringList    &HOList); // FUNNEL TARGET

    static void assertHO(QTextBrowser   *tb)    ;
    static void assertHO(QLineEdit      *line)  ;
    static void assertHO(QPlainTextEdit *pte)   ;
    static void assertHO(QString        &HO)    ;
    static void assertHO(QStringList    &HOList); // FUNNEL TARGET

    static void assertTP(QTextBrowser   *tb)    ;
    static void assertTP(QLineEdit      *line)  ;
    static void assertTP(QPlainTextEdit *pte)   ;
    static void assertTP(QString        &HO)    ;
    static void assertTP(QStringList    &HOList); // FUNNEL TARGET

    static void assertIndex(int &value, int &max);
    static void assertEmpty(QList &value);
    static void assertDivByZero(double &value);
    static void assertOffsetValid (int &newOffset);  // Checks w.r.t. specified offset
    static void assertLengthMatch(int &given, int &expected);
    static void assertInvalidFormat(QString &value);

    // isOM_Type checks both TP and OM
    static void whatOM_Type(omInfo &info, QTextBrowser   *tb)   ;
    static void whatOM_Type(omInfo &info, QLineEdit      *line) ;
    static void whatOM_Type(omInfo &info, QPlainTextEdit *pte)  ;
    static void whatOM_Type(omInfo &info, QString        &input);
    static void whatOM_Type(omInfo &info, QStringList    &input); // FUNNEL TARGET


    static const double MINIMUM_OFFSET = 360000; // 1 Hour in (ms)
    static const double MAXIMUM_OFFSET = 0;

};

#endif // cOM_Common_H

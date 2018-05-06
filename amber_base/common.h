#ifndef COM_COMMON_H
#define COM_COMMON_H
#include <QtCore>
#include <QtWidgets>

class omInfo
{
public:

    omInfo();
    omInfo(const bool &allCondition);
    omInfo(const int  newCondition); // We use Hexadecimal to set this

    QString toString(const bool &type) const;

    bool getIsHO    () const;
    bool getIsTP    () const;
    bool getIsEHO   () const;
    bool getIsSV    () const;
    bool getIsBPM   () const;
    bool getIsNN    () const;
    bool getIsLN    () const;
    bool getLoadFail() const;

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

class amberCommon
{
public:
    amberCommon();

    // Returns info about a HitObject
    static omInfo whatHO(const QTextBrowser   *tb)    ; // V
    static omInfo whatHO(const QLineEdit      *line)  ; // V
    static omInfo whatHO(const QPlainTextEdit *pte)   ; // V
    static omInfo whatHO(const QString        &HO)    ; // V
    static omInfo whatHO(const QStringList    &HOList); // FUNNEL TARGET

    // Returns info about a TimingPoint
    static omInfo whatTP(const QTextBrowser   *tb)    ; // V
    static omInfo whatTP(const QLineEdit      *line)  ; // V
    static omInfo whatTP(const QPlainTextEdit *pte)   ; // V
    static omInfo whatTP(const QString        &TP)    ; // V
    static omInfo whatTP(const QStringList    &TPList); // FUNNEL TARGET

    // Returns info that checks both TP and OM
    static omInfo whatOM_Type(const QTextBrowser   *tb)   ; // V
    static omInfo whatOM_Type(const QLineEdit      *line) ; // V
    static omInfo whatOM_Type(const QPlainTextEdit *pte)  ; // V
    static omInfo whatOM_Type(const QString        &input); // V
    static omInfo whatOM_Type(const QStringList    &input); // FUNNEL TARGET

    // Returns if it's a HitObject
    static bool isHO(const QTextBrowser   *tb)    ; // V
    static bool isHO(const QLineEdit      *line)  ; // V
    static bool isHO(const QPlainTextEdit *pte)   ; // V
    static bool isHO(const QString        &HO)    ; // V
    static bool isHO(const QStringList    &HOList); // FUNNEL TARGET

    // Returns if it's a TimingPoint
    static bool isTP(const QTextBrowser   *tb)    ; // V
    static bool isTP(const QLineEdit      *line)  ; // V
    static bool isTP(const QPlainTextEdit *pte)   ; // V
    static bool isTP(const QString        &HO)    ; // V
    static bool isTP(const QStringList    &HOList); // FUNNEL TARGET

    // Returns if it's a Editor HitObject
    static bool isEHO(const QTextBrowser   *tb)    ; // V
    static bool isEHO(const QLineEdit      *line)  ; // V
    static bool isEHO(const QPlainTextEdit *pte)   ; // V
    static bool isEHO(const QString        &HO)    ; // V
    static bool isEHO(const QStringList    &HOList); // FUNNEL TARGET

    // Throws HOLoadFail if it's not a HitObject
    static void assertHO(const QTextBrowser   *tb)    ; // V
    static void assertHO(const QLineEdit      *line)  ; // V
    static void assertHO(const QPlainTextEdit *pte)   ; // V
    static void assertHO(const QString        &HO)    ; // V
    static void assertHO(const QStringList    &HOList); // FUNNEL TARGET

    // Throws TPLoadFail if it's not a TimingPoint
    static void assertTP(const QTextBrowser   *tb)    ; // V
    static void assertTP(const QLineEdit      *line)  ; // V
    static void assertTP(const QPlainTextEdit *pte)   ; // V
    static void assertTP(const QString        &HO)    ; // V
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

class amberException : public QException
{
public:
    amberException() : msg(""), name("") {}
    amberException(QString newMsg)
    {
        msg = newMsg;
        name = "";
    }
    amberException(QString newMsg, QString newName) : msg(newMsg), name(newName) {}
    QString what()    { return msg; }
    QString excName() { return name; }
protected:
    QString msg ;
    QString name;
};

class columnOutOfRange : public amberException
{
public:
    columnOutOfRange(int    newValue,
                     double min,
                     double max) :
    amberException(QString(QString("Attempt to use column out of range [%1 - %2]: %3")
                           .arg(min)
                           .arg(max)
                           .arg(newValue)),
                   QString("Column out of Range")){}
};
class offsetOutOfRange : public amberException
{
public:
    offsetOutOfRange(double newValue,
                     double min,
                     double max) :
    amberException(QString(QString("Attempt to use offset out of range [%1 - %2]: %3")
                           .arg(min)
                           .arg(max)
                           .arg(newValue)),
                   QString("Offset Out Of Range")){}
};
class keysOutOfRange : public amberException
{
public:
    keysOutOfRange(int newValue,
                   int min,
                   int max) :
    amberException(QString(QString("Attempt to use offset out of range [%1 - %2]: %3")
                           .arg(min)
                           .arg(max)
                           .arg(newValue)),
                   QString("Keys out of Range")){}
};
class xAxisOutOfRange : public amberException
{
public:
    xAxisOutOfRange(int newValue,
                    int min,
                    int max) :
    amberException(QString(QString("Attempt to use xAxis out of range [%1 - %2]: %3")
                           .arg(min)
                           .arg(max)
                           .arg(newValue)),
                   QString("xAxis out of Range")){}
};
class emptyException : public amberException
{
public:
    emptyException(QString objName) :
    amberException(QString(QString("%1 is empty, therefore most functions are not available.")
                           .arg(objName)),
                   QString("Empty Exception")){}
};
class TPLoadFail : public amberException
{
public:
    TPLoadFail(QString newValue) :
    amberException(QString(QString("Failed to load input as TP: %1")
                           .arg(newValue)),
                   QString("TP Load Fail")){}
    TPLoadFail(QStringList newValue) :
    amberException(QString(QString("Failed to load input as TP: %1")
                           .arg((newValue).join("\n"))),
                   QString("TP Load Fail")){}
};
class HOLoadFail : public amberException
{
public:
    HOLoadFail(QString newValue) :
    amberException(QString(QString("Failed to load input as HO: %1")
                           .arg(newValue)),
                   QString("HO Load Fail")){}
    HOLoadFail(QStringList newValue) :
    amberException(QString(QString("Failed to load input as HO: %1")
                           .arg((newValue).join("\n"))),
                   QString("HO Load Fail")){}
};
class indexOutOfRange : public amberException
{
public:
    indexOutOfRange(int newValue,
                    int max) :
    amberException(QString(QString("Index is out of bounds (Given: %1), (Expected: %2)")
                           .arg(newValue)
                           .arg(max)),
                   QString("Index out of Range")){}
};
class lengthMismatch : public amberException
{
public:
    lengthMismatch(int givenLength,
                   int expectedLength) :
    amberException(QString(
                   QString("Length Mismatch (Given: %1), (Expected: %2)")
                           .arg(givenLength)
                           .arg(expectedLength)),
                   QString("Length Mismatch")){}
};
class divideByZeroException : public amberException
{
public:
    divideByZeroException() :
    amberException(QString("Attempted to divide by Zero"),
                   QString("Divide by zero Exception")){}
};
class loadFailException: public amberException
{
public:
    loadFailException(omInfo info) :
    amberException(QString(
                   QString("loadFail is active. loadFailMsg: ")
                           .append((info).getFailMsg())),
                   QString("Load Fail Exception")){}
};




#endif // cOM_Common_H

#ifndef COM_COMMON_H
#define COM_COMMON_H
#include <QtCore>
#include <QtWidgets>
#include "info.h"

class Common
{
public:
    Common();

    // Returns info about a HitObject
    static Info whatHO(const QTextBrowser   *tb)    ; // V
    static Info whatHO(const QLineEdit      *line)  ; // V
    static Info whatHO(const QPlainTextEdit *pte)   ; // V
    static Info whatHO(const QString        &HO)    ; // V
    static Info whatHO(const QStringList    &HOList); // FUNNEL TARGET

    // Returns info about a TimingPoint
    static Info whatTP(const QTextBrowser   *tb)    ; // V
    static Info whatTP(const QLineEdit      *line)  ; // V
    static Info whatTP(const QPlainTextEdit *pte)   ; // V
    static Info whatTP(const QString        &TP)    ; // V
    static Info whatTP(const QStringList    &TPList); // FUNNEL TARGET

    // Returns info that checks both TP and OM
    static Info whatOM_Type(const QTextBrowser   *tb)   ; // V
    static Info whatOM_Type(const QLineEdit      *line) ; // V
    static Info whatOM_Type(const QPlainTextEdit *pte)  ; // V
    static Info whatOM_Type(const QString        &input); // V
    static Info whatOM_Type(const QStringList    &input); // FUNNEL TARGET

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

    // Validate that the index is under maximum specified
    static void assertIndex        (const int &value, const int &max);

    // Validate that the list is not empty
    static void assertEmpty        (const QList<class T> &value, const QString &funcName);
    static void assertEmpty        (const QStringList &value, const QString &funcName);

    // Validate Value is Zero
    static void assertDivByZero    (const double &value);
    static void assertOffsetValid  (const int &newOffset);  // Checks w.r.t. specified offset
    static void assertLengthMatch  (const int &given, const int &expected);
    static void assertInvalidFormat(const QString &value);
    static void assertLoadFail     (const Info &info);

    static constexpr double MINIMUM_OFFSET = 0;
    static constexpr double MAXIMUM_OFFSET = 360000;

};








#endif // cOM_Common_H

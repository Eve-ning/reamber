#ifndef cOM_TPLIST_H
#define cOM_TPLIST_H

#include <cstdlib>
#include "com_tp.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QPlainTextEdit>

class  cOM_TPList
{
public:
    // CONSTRUCTORS
    cOM_TPList()                          ;
    cOM_TPList(QList<cOM_TP> newOM_TPList);
    cOM_TPList(QTextBrowser *tb)          ;
    cOM_TPList(QLineEdit *line)           ;
    cOM_TPList(QPlainTextEdit *pte)       ;
    cOM_TPList(QString str)               ;
    cOM_TPList(QStringList strList)       ;

    // LOADERS
    void loadTPList(QList<cOM_TP>  newOM_TPList);
    void loadTPList(QTextBrowser   *tb);
    void loadTPList(QLineEdit      *line);
    void loadTPList(QPlainTextEdit *pte);
    void loadTPList(QString        &str);
    void loadTPList(QStringList    &str);

    // SETTERS
    void setOffsetList(QList<double> newOffsetList);
    void setCodeList  (QList<double> newCodeList);
    void setValueList (QList<double> newValueList);

    // GETTERS
    QList<double> getOffsetList    (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_BPM_ONLY) const;
    QList<double> getCodeList      (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY) const;
    QList<double> getValueList     (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY) const;
    QList<double> getLengthList    (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_BPM_ONLY) const;
    QList<double> getDistanceList  (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_BPM_ONLY) const;
    QList<double> getUnqOffsetList (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_BPM_ONLY) const;

    cOM_TPList splitByType (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_BPM_ONLY) const;

    double getMinOffset  () const;
    double getMaxOffset  () const;
    double getMinValue   (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY) const;
    double getMaxValue   (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY) const;
    double getLength     () const;
    double getLength     (int index);
    int    getSize       (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_BPM_ONLY) const;
    double getAverage    (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY) const;
    double getDistance   (cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY) const;
    double getDistance   (int index);
    bool   getLoadFail   () const { return loadFail; }
    QStringList toString () const;

    // OPERS
    cOM_TP   operator [](int i) const;
    cOM_TP & operator [](int i);

    void multiplyValue  (const cOM_TPList rhsOM_TPList, bool limitFlag = false);
    void divideValue    (const cOM_TPList rhsOM_TPList, bool limitFlag = false);
    void addValue       (const cOM_TPList rhsOM_TPList, bool limitFlag = false);
    void subtractValue  (const cOM_TPList rhsOM_TPList, bool limitFlag = false);

    void multiplyValue  (const double rhsDouble, bool limitFlag = false);
    void divideValue    (const double rhsDouble, bool limitFlag = false);
    void addValue       (const double rhsDouble, bool limitFlag = false);
    void subtractValue  (const double rhsDouble, bool limitFlag = false);

    void multiplyOffset (const double rhsDouble, bool limitFlag = false);
    void divideOffset   (const double rhsDouble, bool limitFlag = false);
    void addOffset      (const double rhsDouble, bool limitFlag = false);
    void subtractOffset (const double rhsDouble, bool limitFlag = false);

    void zero    ();

    // SORTING
    void sortOffset (const bool isAscending = true);

    // MISC
    void append     (cOM_TP newOM_TP) { OM_TPList.append(newOM_TP); }
    void deleteIndex(unsigned  index) { OM_TPList.removeAt(index); }
    bool isEmpty    () const;
    void limitValues();
    void adjustToAverage (double averageSV, int adjustIndex); // Adjusts a TP so that the average is met
    void makeUnique ();

    cOM_Common::TPFlag isUniform  ();

    QList<int> indexList(cOM_Common::TPFlag onlyFlag = cOM_Common::TPFlag::SV_ONLY);





protected:
    QList<cOM_TP> OM_TPList;
    bool          loadFail;
};

#endif // cOM_TPLIST_H

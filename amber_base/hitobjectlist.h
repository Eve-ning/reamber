#ifndef HitObjectLIST_H
#define HitObjectLIST_H

#include "common.h"
#include "hitobject.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <cstdlib>

class  HitObjectList
{
public:
    // CONSTRUCTORS
    HitObjectList();
    HitObjectList(QList<HitObject> newHOList);
    HitObjectList(QString        EHO    , int newKeys = 0);
    HitObjectList(QTextBrowser   *tb    , int newKeys = 0);
    HitObjectList(QLineEdit      *line  , int newKeys = 0);
    HitObjectList(QPlainTextEdit *pte   , int newKeys = 0);
    HitObjectList(QStringList    strList, int newKeys = 0);

    operator QStringList() const { return toString(); }

    // LOADERS
    void loadHOList (QList<HitObject>  newHOList); // Initialize via array of OM_HO
    void loadHOList (QTextBrowser   *tb     , int newKeys = 0); // TextBrowser Handler
    void loadHOList (QLineEdit      *line   , int newKeys = 0); // LineEdit Handler
    void loadHOList (QPlainTextEdit *pte    , int newKeys = 0); // PlainTextEdit Handler
    void loadHOList (QString        &EHOorHO, int newKeys = 0); // QString Handler
    void loadHOList (QStringList    &HOList , int newKeys = 0); // QStringList Handler

    // SETTERS
    void setOffsetList(QList<double>  &newOffsetList);
    void setXAxisList (QList<double>  &newXAxisList );
    void setColumnList(QList<int>     &newColumnList);
    void setKeys      (unsigned short newKeys       );

    // GETTERS
    QList<double> getOffsetList   () const;
    QList<double> getUnqOffsetList() const;
    QList<double> getXAxisList    () const;
    QList<int>    getColumnList   () const;
    double        getMinOffset    () const;
    double        getMaxOffset    () const;
    double        getLength       () const;
    double        getLength       (int index);
    double        getSize         () const;
    bool          getLoadFail     () const { return loadFail; }
    QStringList   toString        () const;

    // OPERS
    HitObject   operator [](int i) const;
    HitObject & operator [](int i);

    // MISC
    void addColumn      (const int rhsInt);
    void subtractColumn (const int rhsInt);
    void multiplyOffset (const double rhsDouble, bool limitFlag = false);
    void divideOffset   (const double rhsDouble, bool limitFlag = false);
    void addOffset      (const double rhsDouble, bool limitFlag = false);
    void subtractOffset (const double rhsDouble, bool limitFlag = false);

    void makeUnique ();
    void append     (HitObject newOM_HO) { hitObjectList.append(newOM_HO); }
    void deleteIndex(unsigned  index) { hitObjectList.removeAt(index); }
    bool isEmpty    () const;
    void sortOffset (bool isAscending = true);
    void limitColumn (int &maxColumn, int &minColumn);
    void limitColumn ();
    void limitOffset(double minOffset = 0, double maxOffset = 360000);


private:

    void loadEHOList(QString &EHO, int newKeys = 0); // Accessed by loadHO

    QList<HitObject>  hitObjectList;
    bool           loadFail;

};

#endif // HitObjectLIST_H

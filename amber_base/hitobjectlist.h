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
    void setOffsetList(const QList<double>  &newOffsetList);
    void setXAxisList (const QList<double>  &newXAxisList );
    void setColumnList(const QList<int>     &newColumnList);
    void setKeys      (const int &newKeys       );

    // GETTERS
    QList<double> getOffsetList   () const;
    QList<double> getUnqOffsetList() const;
    QList<double> getXAxisList    () const;
    QList<int>    getColumnList   () const;
    double        getMinOffset    () const;
    double        getMaxOffset    () const;
    double        getLength       () const;
    double        getLength       (const int &index);
    double        getSize         () const;
    bool          getLoadFail     () const { return loadFail; }
    QStringList   toString        () const;

    // OPERS
    HitObject   operator [](int i) const;
    HitObject & operator [](int i);

    // MISC
    void addColumn      (const int &rhsInt);
    void subtractColumn (const int &rhsInt);
    void multiplyOffset (const double &rhsDouble, const bool &limitFlag = false);
    void divideOffset   (const double &rhsDouble, const bool &limitFlag = false);
    void addOffset      (const double &rhsDouble, const bool &limitFlag = false);
    void subtractOffset (const double &rhsDouble, const bool &limitFlag = false);

    void makeUnique ();
    void append     (const HitObject &newOM_HO) { hitObjectList.append(newOM_HO); }
    void deleteIndex(int &index) { hitObjectList.removeAt(index); }
    bool isEmpty    () const;
    void sortOffset (const bool &isAscending = true);
    void limitColumn (const int &maxColumn, const int &minColumn);
    void limitColumn ();
    void limitOffset(const double &minOffset = 0, const double &maxOffset = 360000);


private:

    void loadEHOList(QString &EHO, int newKeys = 0); // Accessed by loadHO

    QList<HitObject> hitObjectList;
    bool             loadFail;

};

#endif // HitObjectLIST_H

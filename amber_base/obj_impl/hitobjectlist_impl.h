#ifndef HITOBJECTLIST_IMPL_H
#define HITOBJECTLIST_IMPL_H
#include "amber_base/hitobject.h" // We include the derived
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QPlainTextEdit>
#include <cstdlib>

class HitObjectList_impl
{
public:
    HitObjectList_impl();

    operator QStringList() const { return toString(); }

    // LOADERS
    void loadHOList (QList<HitObject>  newHOList); // Initialize via array of OM_HO
    void loadHOList (QTextBrowser   *tb     , Keys newKeys = 0); // TextBrowser Handler
    void loadHOList (QLineEdit      *line   , Keys newKeys = 0); // LineEdit Handler
    void loadHOList (QPlainTextEdit *pte    , Keys newKeys = 0); // PlainTextEdit Handler
    void loadHOList (QString        &HO_, Keys newKeys = 0); // QString Handler
    void loadHOList (QStringList    &HOList , Keys newKeys = 0); // QStringList Handler

    // SETTERS
    void setOffsetList(const QList<Offset>  &newOffsetList);
    void setXAxisList (const QList<XAxis>  &newXAxisList );
    void setColumnList(const QList<Column>     &newColumnList);
    void setKeys      (const Keys &newKeys       );

    // GETTERS
    QList<Offset> getOffsetList   () const;
    QList<Offset> getUnqOffsetList() const;
    QList<XAxis>  getXAxisList    () const;
    QList<Column> getColumnList   () const;
    Offset        getMinOffset    () const;
    Offset        getMaxOffset    () const;
    Offset        getLength       () const;
    Offset        getLength       (const int &index);
    int           getSize         () const;
    bool          getLoadFail     () const { return loadFail; }
    QStringList   toString        () const;

    // OPERS
    HitObject   operator [](int i) const;
    HitObject & operator [](int i);

    // MISC
    void addColumn      (const Column &rhsInt);
    void subtractColumn (const Column &rhsInt);
    void multiplyOffset (const double &rhsDouble);
    void divideOffset   (const double &rhsDouble);
    void addOffset      (const double &rhsDouble);
    void subtractOffset (const double &rhsDouble);

    void makeUnique ();
    void append     (const HitObject &newOM_HO){ hitObjectList.append(newOM_HO); }
    void deleteIndex(int &index){ hitObjectList.removeAt(index); }
    bool isEmpty    () const;
    void sortOffset (const bool &isAscending = true);


private:

    void loadEHOList(QString &EHO, Keys newKeys = 0); // Accessed by loadHO

    QList<HitObject> hitObjectList;
    bool             loadFail;

};

#endif // HITOBJECTLIST_IMPL_H

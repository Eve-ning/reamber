#ifndef AAOBJ_H
#define AAOBJ_H

#include "aaform.h"
#include "ui_aaform.h"
#include "amber_base_inc.h"
#include <QtCore>

class AAName
{

public:
    AAName(int newType)
    {
        load(newType);
    }
    AAName(QString newName)
    {
        load(newName);
    }
    AAName()
    {
        load(0);
    }

    void load(QString newName);
    void load(int newIndex);

    int getIndex() const
    {
        return nameList.indexOf(name);
    }
    QString getName() const
    {
        return name;
    }

    void setIndex(int newType)
    {
        load(newType);
    }
    void setName(QString newName)
    {
        load(newName);
    }

    static const QStringList getNameList()
    {
        return nameList;
    }
    static int getIndexOf(QString newName)
    {
        return nameList.indexOf(newName);
    }

protected:
    QString name;
    static const QStringList nameList;
};

struct AAData
{
public:
AAData()
    : pte(""),
      line_1(""),
      line_2(""),
      line_3(""),
      line_4(""),
      line_5(""),
      line_6(""),
      chkbx_1(false),
      chkbx_2(false),
      chkbx_3(false),
      radio_1(false),
      radio_2(false),
      radio_3(false) {}

bool isDefault(){
    return (pte     = ""    ||
            line_1  = ""    ||
            line_2  = ""    ||
            line_3  = ""    ||
            line_4  = ""    ||
            line_5  = ""    ||
            line_6  = ""    ||
            chkbx_1 = false ||
            chkbx_2 = false ||
            chkbx_3 = false ||
            radio_1 = false ||
            radio_2 = false ||
            radio_3 = false );
}
void toDefault(){
    AAData();
}

AAData(pte_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, chkbx_1_,
       chkbx_2_, chkbx_3_, radio_1_, radio_2_, radio_3_)
    : pte(pte_),
      line_1(line_1_),
      line_2(line_2_),
      line_3(line_3_),
      line_4(line_4_),
      line_5(line_5_),
      line_6(line_6_),
      chkbx_1(chkbx_1_),
      chkbx_2(chkbx_2_),
      chkbx_3(chkbx_3_),
      radio_1(radio_1_),
      radio_2(radio_2_),
      radio_3(radio_3_) {}

QString pte, line_1, line_2, line_3, line_4, line_5, line_6;
bool chkbx_1, chkbx_2, chkbx_3, radio_1, radio_2, radio_3;
};

class AAObj
{
public:

    AAObj(AAName newObjType);
    ~AAObj();

    void setForm();
    void showForm();
    void grabData();
    void closeForm();

    void setFormDefault();
    void setObjType(AAName newObjType);

    TimingPointList applyEffect(TimingPointList oldTPList);

    AAName getEffect();
    QString getEffectName(bool getInfo = false);

    AAData getData() const;


    // Need to somehow pass data from form to here
public slots:
    void setData(const AAData &value);

protected:

    AAName objName;
    AAForm *ui;
    AAData data;

};

#endif // AAOBJ_H

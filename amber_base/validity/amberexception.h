#ifndef AEXC_H
#define AEXC_H
#include <QException>
#include <QDebug>


// Note that QT doesn't support exceptions,
// so this acts via qDebug to warn implementers

class AmberException
{
public:
    AmberException() :
        index(-1), custMsg("NO ERROR"){}
    AmberException(int newIndex, const QString &newCustMsg = "") :
        index(newIndex), custMsg(newCustMsg){
        raise();
    }
    QString what() const {
        if (index == -1){ return ""; }
        return presetMsgs[index].msg + '\n' + custMsg;
    }

    void raise() const
    {
        qDebug() << what();
    }
    // Pre-defined message struct
    struct presetMsg {
        presetMsg(int newIndex, QString newMsg) :
            index(newIndex),
            msg(newMsg){}

        int index;
        QString msg;
    };


    // Enumeration of all preset index ints
    enum msgIndex
    {
        GENERAL_ERROR,
        UNEXPECTED_ERROR,
        INDEX_OUT_OF_RANGE,
        VALUE_OUT_OF_RANGE,
        IS_EMPTY,
        TP_LOADFAIL,
        HO_LOADFAIL,
        EHO_LOADFAIL,
        MAP_LOADFAIL,
        LENGTH_MISMATCH,
        DIVIDE_BY_ZERO,
        LOADFAIL_RESTRICT,
        INFO_RESTRICT,
        FILE_COPY_FAIL
    };

    // Validate that the index is under maximum specified
    static void assertIndex        (const int &value,
                                    const int &max);

    // Validate Value is Zero
    static void assertLengthMatch  (const int &given,
                                    const int &expected);
    static void assertInvalidFormat(const QString &value);

protected:
    // List for Preset Messages
    QList<presetMsg> presetMsgs =
    {
        presetMsg(GENERAL_ERROR     , "A general error has been thrown."),
        presetMsg(UNEXPECTED_ERROR  , "An unexpected error has occured."),
        presetMsg(INDEX_OUT_OF_RANGE, "Index selected was out of range of memory."),
        presetMsg(VALUE_OUT_OF_RANGE, "Value provided was out of range."),
        presetMsg(IS_EMPTY          , "Functions cannot operate while list is empty."),
        presetMsg(TP_LOADFAIL       , "Timing Point didn't load successfully."),
        presetMsg(HO_LOADFAIL       , "Hit Object didn't load successfully."),
        presetMsg(EHO_LOADFAIL      , "Editor Hit Object didn't load successfully."),
        presetMsg(MAP_LOADFAIL      , "Map didn't load successfully."),
        presetMsg(LENGTH_MISMATCH   , "Function failed due to mismatch in length given."),
        presetMsg(DIVIDE_BY_ZERO    , "Attempted to divide by zero."),
        presetMsg(LOADFAIL_RESTRICT , "Functions are restricted when loadFail is active."),
        presetMsg(INFO_RESTRICT     , "Certain functions only allow certain Info inputs."),
        presetMsg(FILE_COPY_FAIL    , "File didn't copy successfully.")
    };
    int index;
    QString custMsg;
};





#endif // AEXC_H

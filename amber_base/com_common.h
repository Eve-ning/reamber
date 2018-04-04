#ifndef COM_COMMON_H
#define COM_COMMON_H
#include <QtCore>
#include <QtWidgets>

class cOM_Common
{
public:
    cOM_Common();

    enum class TPFlag
    {
        SV_BPM_ONLY,
        SV_ONLY    ,
        BPM_ONLY   ,
        INVALID
    };

    enum class HOFlag
    {
        NN_LN_ONLY,
        NN_ONLY   ,
        LN_ONLY   ,
        INVALID
    };

    enum class EHOFlag
    {
        EHO_ONLY,
        INVALID
    };

    enum class OMFlag
    {
        TP_ONLY,
        EHO_ONLY,
        HO_ONLY,
        MULTIPLETYPES,
        INVALID
    };

    static cOM_Common::HOFlag isHO(QTextBrowser   *tb);
    static cOM_Common::HOFlag isHO(QLineEdit      *line);
    static cOM_Common::HOFlag isHO(QPlainTextEdit *pte);
    static cOM_Common::HOFlag isHO(QString         HO);
    static cOM_Common::HOFlag isHO(QStringList     HO);

    static cOM_Common::TPFlag isTP(QTextBrowser   *tb);
    static cOM_Common::TPFlag isTP(QLineEdit      *line);
    static cOM_Common::TPFlag isTP(QPlainTextEdit *pte);
    static cOM_Common::TPFlag isTP(QString         TP);
    static cOM_Common::TPFlag isTP(QStringList     TP);

    static cOM_Common::EHOFlag isEHO(QTextBrowser   *tb);
    static cOM_Common::EHOFlag isEHO(QLineEdit      *line);
    static cOM_Common::EHOFlag isEHO(QPlainTextEdit *pte);
    static cOM_Common::EHOFlag isEHO(QString         EHO);
    static cOM_Common::EHOFlag isEHO(QStringList     EHO);

    static cOM_Common::OMFlag isOM_Type(QTextBrowser   *tb);
    static cOM_Common::OMFlag isOM_Type(QLineEdit      *line);
    static cOM_Common::OMFlag isOM_Type(QPlainTextEdit *pte);
    static cOM_Common::OMFlag isOM_Type(QString         input);
    static cOM_Common::OMFlag isOM_Type(QStringList     input);
};

#endif // cOM_Common_H

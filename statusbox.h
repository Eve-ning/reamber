#ifndef STATUSBOX_H
#define STATUSBOX_H
#include <QString>
#include <QStringList>
#include <QTextBrowser>


namespace STATUSBOX
{
    void sendMsg (QTextBrowser *tb, QString message, QString tag = ""); //ends custom message through amber::appendMessages
    void sendMsg (QTextBrowser *tb, QStringList messageList, QString tag = ""); //ends custom message through amber::appendMessages
    void sendMsg (QTextBrowser *tb, QList<double> messageList, QString tag = "");
    void sendMsg (QTextBrowser *tb, QList<int> messageList, QString tag);
    void clearBox(QTextBrowser *tb); //lears status box
}

/* Redacted for other error parsing methods.
enum STATUSENUM {

    //HECK
    CHECK_EHO_PASS                  =   0,
    CHECK_HO_PASS                   =   1,
    CHECK_TP_PASS                   =   2,

    CHECK_EHO_FAIL                  =   3,
    CHECK_HO_FAIL                   =   4,
    CHECK_TP_FAIL                   =   5,

    //HECK
    CHECK_HO_NN_PASS                =   6,
    CHECK_HO_LN_PASS                =   7,
    CHECK_TP_SV_PASS                =   8,
    CHECK_TP_BPM_PASS               =   9,

    CHECK_HO_NN_FAIL                =   10,
    CHECK_HO_LN_FAIL                =   11,
    CHECK_TP_SV_FAIL                =   12,
    CHECK_TP_BPM_FAIL               =   13,

    //ONVERT
    CONVERT_COLUMN_CODEtoVALUE_PASS =   100,
    CONVERT_COLUMN_VALUEtoCODE_PASS =   101,
    CONVERT_EHOtoOFFSETLIST_PASS    =   102,
    CONVERT_EHOtoCOLUMNLIST_PASS    =   103,
    CONVERT_HOtoOFFSETLIST_PASS     =   104,
    CONVERT_HOtoCOLUMNLIST_PASS     =   105,
    CONVERT_HOtoEXTENSIONLIST_PASS  =   106,
    CONVERT_TPtoOFFSETLIST_PASS     =   107,
    CONVERT_TPtoVALUELIST_PASS      =   108,
    CONVERT_TPtoCODELIST_PASS       =   109,
    CONVERT_TPtoSVVALUELIST_PASS    =   110,
    CONVERT_TPtoBPMVALUELIST_PASS   =   111,
    CONVERT_TPtoSVCODELIST_PASS     =   112,
    CONVERT_TPtoBPMCODELIST_PASS    =   113,
    CONVERT_TP_BPMCODEtoVALUE_PASS  =   114,
    CONVERT_TP_BPMVALUEtoCODE_PASS  =   115,
    CONVERT_TP_SVCODEtoVALUE_PASS   =   116,
    CONVERT_TP_SVVALUEtoCODE_PASS   =   117,
    CONVERT_OMtoBASIC_PASS          =   118,
    CONVERT_BASICtoOM_PASS          =   119,

    CONVERT_COLUMN_CODEtoVALUE_FAIL =   120,
    CONVERT_COLUMN_VALUEtoCODE_FAIL =   121,
    CONVERT_EHOtoOFFSETLIST_FAIL    =   122,
    CONVERT_EHOtoCOLUMNLIST_FAIL    =   123,
    CONVERT_HOtoOFFSETLIST_FAIL     =   124,
    CONVERT_HOtoCOLUMNLIST_FAIL     =   125,
    CONVERT_HOtoEXTENSIONLIST_FAIL  =   126,
    CONVERT_TPtoOFFSETLIST_FAIL     =   127,
    CONVERT_TPtoVALUELIST_FAIL      =   128,
    CONVERT_TPtoCODELIST_FAIL       =   129,
    CONVERT_TPtoSVVALUELIST_FAIL    =   130,
    CONVERT_TPtoBPMVALUELIST_FAIL   =   131,
    CONVERT_TPtoSVCODELIST_FAIL     =   132,
    CONVERT_TPtoBPMCODELIST_FAIL    =   133,
    CONVERT_TP_BPMCODEtoVALUE_FAIL  =   134,
    CONVERT_TP_BPMVALUEtoCODE_FAIL  =   135,
    CONVERT_TP_SVCODEtoVALUE_FAIL   =   136,
    CONVERT_TP_SVVALUEtoCODE_FAIL   =   137,
    CONVERT_OMtoBASIC_FAIL          =   138,
    CONVERT_BASICtoOM_FAIL          =   139,

    //OMPILE
    COMPILE_OM_NN_PASS              =   200,
    COMPILE_OM_LN_PASS              =   201,
    COMPILE_OM_BPM_PASS             =   202,
    COMPILE_OM_SV_PASS              =   203,
    COMPILE_BASIC_HO_PASS           =   204,
    COMPILE_BASIC_TP_PASS           =   205,

    COMPILE_OM_NN_FAIL              =   206,
    COMPILE_OM_LN_FAIL              =   207,
    COMPILE_OM_BPM_FAIL             =   208,
    COMPILE_OM_SV_FAIL              =   209,
    COMPILE_BASIC_HO_FAIL           =   210,
    COMPILE_BASIC_TP_FAIL           =   211,

    //INK
    LINK_REPO_PASS                  =   300,
    LINK_WIKI_PASS                  =   301,
    LINK_RELEASES_PASS              =   302,
    LINK_CONTACT_PASS               =   303,

    LINK_REPO_FAIL                  =   304,
    LINK_WIKI_FAIL                  =   305,
    LINK_RELEASES_FAIL              =   306,
    LINK_CONTACT_FAIL               =   307

};
*/

#endif // STATUSBOX_H

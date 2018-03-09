#ifndef DEFARGS_H
#define DEFARGS_H

#include <QString>
#include <QTextBrowser>

namespace DEFARGS {

    extern  QString xAxis
                    ,yAxis
                    ,offset
                    ,lnParameter
                    ,lnOffset
                    ,bpmCode
                    ,svCode
                    ,bpmValue
                    ,svValue
                    ,column
                    ,noOfKeys
                    ,timingPointLabel
                    ,hitObjectLabel
                    ,nnExtension
                    ,lnExtension
                    ,bpmExtension
                    ,svExtension
                    ,timingPointType
                    ;

    extern  int     HO_LABEL
                    ,HO_NOOFKEYS
                    ,HO_OFFSET
                    ,HO_COLUMN
                    ,HO_LNENDOFFSET
                    ,TP_LABEL
                    ,TP_OFFSET
                    ,TP_VALUE
                    ,TP_TYPE
                    ;
}

#endif // DEFARGS_H

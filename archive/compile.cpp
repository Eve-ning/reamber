//#include "compile.h"

//namespace COMPILE {

////ompilers
//QString OM_NN(QTextBrowser *tb,
//              HitObject &OM_HO)
//{
//    QString output;
//    /* Normal Note: xAxis,yAxis,offset,extension */
//    output = OM_HO.toString();
//    STATMSG("Output: " + output);
//    return output;
//}

//QString OM_LN(QTextBrowser *tb,
//              HitObject &OM_HO)
//{
//    QString output;
//    /* Long Note: xAxis,yAxis,offset,parameter,lnOffset&extension */
//    output = OM_HO.toString();
//    STATMSG("Output: " + output);
//    return output;
//}

//QString OM_BPM(QTextBrowser *tb,
//               TimingPoint &OM_TP)
//{
//    QString output;
//    /* BPM Line: offset,code,extension */
//    OM_TP.limitValue();
//    output = OM_TP.toString();
//    STATMSG("Output: " + output);
//    return output;
//}

//QString OM_SV(QTextBrowser *tb,
//              TimingPoint &OM_TP)
//{
//    QString output;
//    /* SV Line: offset,code,extension */
//    OM_TP.limitValue();
//    output = OM_TP.toString();
//    STATMSG("Output: " + output);
//    return output;
//}

////String BASIC_HO(QTextBrowser *tb,
////                 QString noOfKeys,
////                 QString offset,
////                 QString column,
////                 QString lnOffset,
////                 QString label)
////{
////    QString output;
////    /* HITOBJECT: HITOBJECT|NO_OF_KEYS|OFFSET|COLUMN|LN_OFFSET */
////    output = label
////            + ("|")
////            + (noOfKeys)
////            + ("|")
////            + (offset)
////            + ("|")
////            + (column)
////            + ("|")
////            + (lnOffset);
////    STATMSG("Output: " + output)
////    return output;
////}

////String BASIC_TP(QTextBrowser *tb,
////                 QString offset,
////                 QString value,
////                 QString timingPointType,
////                 QString label)
////{
////    QString output;
////    /* TIMINGPOINT: TIMINGPOINT|OFFSET|VALUE|TYPE */
////    output = label
////            + ("|")
////            + (offset)
////            + ("|")
////            + (value)
////            + ("|")
////            + (timingPointType);
////    STATMSG("Output: " + output)
////    return output;
////}

///* ProcOutput
//void ProcOutput(QTextBrowser *inputBoxObject,
//                QTextBrowser *outputBoxObject)
//{
//    QStringList partVector, rawOutputVector;
//    QString rawOutputString;
//    double columnCode, timingPointCode;

//    //lear outputBox
//    outputBoxObject->clear();

//    //oad procOutput into Vector
//    rawOutputVector = inputBoxObject->toPlainText().split("\n");

//    foreach(rawOutputString, rawOutputVector){
//        partVector = rawOutputString.split("|",QString::SkipEmptyParts);

//        if (partVector[DEFARGS::HO_LABEL] == "HITOBJECT")
//        {
//            //itObjectOutput
//            //alculation of ColumnCode
//            columnCode = CONVERT::COLUMN_VALUEtoCODE(partVector[DEFARGS::HO_COLUMN].toDouble(),
//                                                             partVector[DEFARGS::HO_NOOFKEYS].toDouble());
//            if (partVector[DEFARGS::HO_LNENDOFFSET] == "-1")
//            {
//                //ormal Note Compile
//                outputBoxObject->append(OM_NN(QString::number(columnCode),
//                                                                      partVector[DEFARGS::HO_OFFSET]));
//            }
//            else
//            {
//                //ong Note Compile
//                outputBoxObject->append(OM_LN(QString::number(columnCode),
//                                                                      partVector[DEFARGS::HO_OFFSET],
//                                                                      partVector[DEFARGS::HO_LNENDOFFSET]));
//            }

//        }
//        else if (partVector[DEFARGS::TP_LABEL] == "TIMINGPOINT")
//        {
//            //imingPointOutput
//            if (partVector[DEFARGS::TP_TYPE] == "BPM")
//            {
//                //PM Compile
//                timingPointCode = 60000 / partVector[DEFARGS::TP_VALUE].toDouble();
//                outputBoxObject->append(OM_BPM(partVector[DEFARGS::TP_OFFSET],
//                                                                       QString::number(timingPointCode)));
//            }
//            else if (partVector[DEFARGS::TP_TYPE] == "BPM")
//            {
//                //V Compile
//                timingPointCode = -100 / partVector[DEFARGS::TP_VALUE].toDouble();
//                outputBoxObject->append(OM_SV(partVector[DEFARGS::TP_OFFSET],
//                                                                      QString::number(timingPointCode)));
//            }
//        }
//        else
//        {
//            //ullOutput
//            continue;
//        }
//    }
//}
//*/
//}

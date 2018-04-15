#include <QCoreApplication>
#include <QDebug>
#include "com_map.h"
#include "com_math.h"

void calibrate();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    calibrate();

    return a.exec();
}

void calibrate(){

    bool mapDebugBool     = true,
         TPDebugBool      = false,
         sortDebugBool    = false,
         unqDebugBool     = false,
         omTypeDebugBool  = false;

    // Map Debug
    if (mapDebugBool){

        QFileInfo mapFile;

        mapFile.setFile("D:\\osu!\\Songs\\165991 Reol - +Danshi\\Reol - +Danshi (lZenxl) [7K NM].osu");

        cOM_Map map;

        map.loadMap(mapFile);

        map.getInfo();

        for (int temp = 0; temp < 1; temp ++) {
            map.getOM_HOList ()[temp].getInfo();
            map.getOM_TPList ()[temp].getInfo();
            map.getBreakPList()[temp].getInfo(); // Maps may not have breaks
        }
    }
    if (TPDebugBool){

        // [--- OPERATORS ---]
        cOM_TPList TPList_A_add,
                   TPList_A_subtract,
                   TPList_A_multiply,
                   TPList_A_divide,

                   TPList_B;
        /* Visualization
         *
         * Each bar represents 10000ms
         *    [1] [2] [3] [4] [5] [6] [7] [8] [9]
         * A |0.5|   |1.0|2.0|   |   |0.1|0.5|   |
         * B |   |2.0|   |5.0|4.0|2.0|   |   |0.4|
         */

        TPList_A_add      =
        TPList_A_subtract =
        TPList_A_multiply =
        TPList_A_divide   = QStringList({
            "10000,-200,4,2,1,80,0,0" , // [1]
            "30000,-100,4,2,1,80,0,0" , // [3]
            "40000,-50,4,2,1,80,0,0"  , // [4]
            "70000,-1000,4,2,1,80,0,0", // [7]
            "80000,-200,4,2,1,80,0,0"   // [8]
                   });

        TPList_B = QStringList({
            "20000,-50,4,2,1,80,0,0"  , // [2]
            "40000,-20,4,2,1,80,0,0"  , // [4]
            "50000,-25,4,2,1,80,0,0"  , // [5]
            "60000,-50,4,2,1,80,0,0"  , // [6]
            "90000,-250,4,2,1,80,0,0"   // [9]
                   });

        TPList_A_add     .addValue     (TPList_B);
        TPList_A_subtract.subtractValue(TPList_B);
        TPList_A_multiply.multiplyValue(TPList_B);
        TPList_A_divide  .divideValue  (TPList_B);

        qDebug() << "[--- ADD ---]";
        qDebug() << "          " << TPList_A_add.getValueList();
        qDebug() << "Expected : (0.5, 3, 7, 2.1, 2.5)" << "\n";

        qDebug() << "[--- subtract ---]";
        qDebug() << "          " << TPList_A_subtract.getValueList();
        qDebug() << "Expected : (0.5, -1, -3, -1.9, -1.5)" << "\n";

        qDebug() << "[--- MULTIPLY ---]";
        qDebug() << "          " << TPList_A_multiply.getValueList();
        qDebug() << "Expected : (0.5, 2, 10, 0.2, 1)" << "\n";

        qDebug() << "[--- DIVIDE ---]";
        qDebug() << "          " << TPList_A_divide.getValueList();
        qDebug() << "Expected : (0.5, 0.5, 0.4, 0.05, 0.25)" << "\n";

        // [--- ADJUST TO AVERAGE ---]

        cOM_TPList TPList_A_adjust;

        /* Visualization
         *
         * Each bar represents 10000ms
         *    [1] [2] [3] [4] [5] [6] [7] [8]
         * A |0.5|   |1.0|2.0|   |   |0.1|0.5|
         *
         * Current Average: 1.075
         *
         *
         *                 [ADJ]
         *    [1] [2] [3]   [4]  [5] [6] [7] [8]
         * A |0.5|   |1.0|1.6333|   |   |0.1|0.5|
         *
         * New Average: 1.0
         */

        TPList_A_adjust   = QStringList({
            "10000,-200,4,2,1,80,0,0" , // [1]
            "30000,-100,4,2,1,80,0,0" , // [3]
            "40000,-50,4,2,1,80,0,0"  , // [4]
            "70000,-1000,4,2,1,80,0,0", // [7]
            "80000,-200,4,2,1,80,0,0"   // [8]
                   });

        TPList_A_adjust.adjustToAverage(1.0,2);

        qDebug() << "[--- ADJUST TO AVERAGE ---]";
        qDebug() << "         " << TPList_A_adjust.getValueList();
        qDebug() << "Expected: (0.5, 1, 1.63333, 0.1, 0.5)" << "\n";

        TPList_A_adjust.adjustToAverage(1.3,3);

        qDebug() << "[--- ADJUST TO AVERAGE <DIFFERENT INDEX> ---]";
        qDebug() << "         " << TPList_A_adjust.getValueList();
        qDebug() << "Expected: (0.5, 1, 1.63333, 2.2, 0.5)" << "\n";

        TPList_A_adjust.adjustToAverage(10.0,2);

        qDebug() << "[--- ADJUST TO AVERAGE <MAX EXCEED> ---]";
        qDebug() << "         " << TPList_A_adjust.getValueList();
        qDebug() << "Expected: (0.5, 1, 10, 2.2, 0.5)" << "\n";

        TPList_A_adjust.adjustToAverage(10.0,4);

        qDebug() << "[--- ATTEMPT TO ADJUST LAST INDEX ---]";
        qDebug() << "         " << TPList_A_adjust.getValueList();
        qDebug() << "Expected: (0.5, 1, 10, 2.2, 0.5)" << "\n";


    }
    if (sortDebugBool){
        cOM_HOList HOList ("00:00:257 (299|4,291|5,3432|6,38025|4,4128|5,557|4) - ", 7);

        qDebug() << "Original   : " << HOList.getOffsetList() << HOList.getColumnList();
        HOList.sortOffset(true);
        qDebug() << "Ascending  : " << HOList.getOffsetList() << HOList.getColumnList();
        HOList.sortOffset(false);
        qDebug() << "Descending : " << HOList.getOffsetList() << HOList.getColumnList();
    }
    if (unqDebugBool){

        cOM_HOList temp("00:00:000 (0|2,0|0,0|1,165|4,341|2,341|1,518|4) - ", 7);

        qDebug() << "<OFFSET> Original : " << temp.getOffsetList();
        qDebug() << "<COLUMN> Original : " << temp.getColumnList();

        temp.makeUnique();

        qDebug() << "<OFFSET> Unique   : " << temp.getOffsetList();
        qDebug() << "<COLUMN> Unique   : " << temp.getColumnList();
    }
    if (omTypeDebugBool)
    {
        QString EHO,
                HO,
                TP,
                MLT,
                INV;

        EHO = "00:03:543 (3543|1,3622|2,3701|3,3780|2,3859|1,3938|0,4016|1,4095|2) - ";

        HO  = "64,192,22185,1,0,0:0:0:0:\n"
              "192,192,22259,1,0,0:0:0:0:";

        TP  = "810,294.840294840295,4,1,0,5,1,0\n"
              "815,294.840294840295,4,1,0,5,1,0";

        MLT = "52138,144,4,1,0,45,1,0\n"
              "52138,144,4,1,0,45,1,0\n"
              "192,192,22259,1,0,0:0:0:0:";

        INV = "810,294.840294840295,4,1,0,5,1,0\n"
              "pancake,peanuts,and,beets\n"
              "192,192,22259,1,0,0:0:0:0:";

        qDebug() << "[--- EHO ---]";
        qDebug() << "EHO: " << (cOM_Common::isOM_Type(EHO) == cOM_Common::OMFlag::EHO_ONLY)      << " | "
                 << "HO : " << (cOM_Common::isOM_Type(EHO) == cOM_Common::OMFlag::HO_ONLY)       << " | "
                 << "TP : " << (cOM_Common::isOM_Type(EHO) == cOM_Common::OMFlag::TP_ONLY)       << " | "
                 << "MLT: " << (cOM_Common::isOM_Type(EHO) == cOM_Common::OMFlag::MULTIPLETYPES) << " | "
                 << "IVL: " << (cOM_Common::isOM_Type(EHO) == cOM_Common::OMFlag::INVALID)       << "\n";

        qDebug() << "[--- HO ---]";
        qDebug() << "EHO: " << (cOM_Common::isOM_Type(HO) == cOM_Common::OMFlag::EHO_ONLY)      << " | "
                 << "HO : " << (cOM_Common::isOM_Type(HO) == cOM_Common::OMFlag::HO_ONLY)       << " | "
                 << "TP : " << (cOM_Common::isOM_Type(HO) == cOM_Common::OMFlag::TP_ONLY)       << " | "
                 << "MLT: " << (cOM_Common::isOM_Type(HO) == cOM_Common::OMFlag::MULTIPLETYPES) << " | "
                 << "IVL: " << (cOM_Common::isOM_Type(HO) == cOM_Common::OMFlag::INVALID)       << "\n";

        qDebug() << "[--- TP ---]";
        qDebug() << "EHO: " << (cOM_Common::isOM_Type(TP) == cOM_Common::OMFlag::EHO_ONLY)      << " | "
                 << "HO : " << (cOM_Common::isOM_Type(TP) == cOM_Common::OMFlag::HO_ONLY)       << " | "
                 << "TP : " << (cOM_Common::isOM_Type(TP) == cOM_Common::OMFlag::TP_ONLY)       << " | "
                 << "MLT: " << (cOM_Common::isOM_Type(TP) == cOM_Common::OMFlag::MULTIPLETYPES) << " | "
                 << "IVL: " << (cOM_Common::isOM_Type(TP) == cOM_Common::OMFlag::INVALID)       << "\n";

        qDebug() << "[--- MLT ---]";
        qDebug() << "EHO: " << (cOM_Common::isOM_Type(MLT) == cOM_Common::OMFlag::EHO_ONLY)      << " | "
                 << "HO : " << (cOM_Common::isOM_Type(MLT) == cOM_Common::OMFlag::HO_ONLY)       << " | "
                 << "TP : " << (cOM_Common::isOM_Type(MLT) == cOM_Common::OMFlag::TP_ONLY)       << " | "
                 << "MLT: " << (cOM_Common::isOM_Type(MLT) == cOM_Common::OMFlag::MULTIPLETYPES) << " | "
                 << "IVL: " << (cOM_Common::isOM_Type(MLT) == cOM_Common::OMFlag::INVALID)       << "\n";

        qDebug() << "[--- INV ---]";
        qDebug() << "EHO: " << (cOM_Common::isOM_Type(INV) == cOM_Common::OMFlag::EHO_ONLY)      << " | "
                 << "HO : " << (cOM_Common::isOM_Type(INV) == cOM_Common::OMFlag::HO_ONLY)       << " | "
                 << "TP : " << (cOM_Common::isOM_Type(INV) == cOM_Common::OMFlag::TP_ONLY)       << " | "
                 << "MLT: " << (cOM_Common::isOM_Type(INV) == cOM_Common::OMFlag::MULTIPLETYPES) << " | "
                 << "IVL: " << (cOM_Common::isOM_Type(INV) == cOM_Common::OMFlag::INVALID)       << "\n";
    }


}

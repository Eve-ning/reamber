#include "aaobj.h"

AAObj::AAObj(AAType newObjType)
{
    objType = newObjType;
    ui = new AAForm;
}

AAObj::~AAObj()
{
    delete ui;
    ui = nullptr;
}

void AAObj::showForm()
{
    ui->show();
}
void AAObj::closeForm()
{
    ui->close();
}
void AAObj::setFormDefault()
{
    ui->disableAll();
}
void AAObj::setForm()
{
    // Reset everything to default
    setFormDefault();

    // Sets UI Form according to Object Type
    switch (objType)
    {
    case AAType::ADD_OFFSET     :
        ui->enableLine(0);
        ui->setLineTitle("Offset (+ms):", 0, "Insert Offset Here.");
        break;
    case AAType::ADD_VALUE      :
        ui->enableLine(0);
        ui->setLineTitle("Value (+):", 0, "Insert Value Here.");
        break;
    case AAType::MULT_OFFSET    :
        ui->enableLine(0);
        ui->setLineTitle("Value (*):", 0, "Insert Offset Here.");
        break;
    case AAType::MULT_VALUE     :
        ui->enableLine(0);
        ui->setLineTitle("Value (*):", 0, "Insert Value Here.");
        break;
    case AAType::DEL_SV         :
        // No Form
        break;
    case AAType::DEL_BPM        :
        // No Form
        break;
    case AAType::CONV_SV        :
        // No Form
        break;
    case AAType::CONV_BPM       :
        // No Form
        break;
    case AAType::ADD_TPLIST     :
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Add.>");
        break;
    case AAType::SUBTRACT_TPLIST:
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Subtract.>");
        break;
    case AAType::MULT_TPLIST    :
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Multiply.>");
        break;
    case AAType::DIV_TPLIST     :
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Divide.>");
        break;
    case AAType::INVERT         :
        ui->enableLine(0);

        ui->setLineTitle("Invert along X-axis", 0,"y = ?");

        ui->enableChkbx(0);
        ui->enableChkbx(1);

        ui->setChkbxTitle("Invert Settings");
        ui->setChkbxText("Invert SV", 0);
        ui->setChkbxText("Invert BPM", 1);

        // Default these as checked
        ui->checkChkbx(0, true);
        ui->checkChkbx(1, true);

        break;
    case AAType::LIMITVAL       :
        ui->enableLine(0);
        ui->enableLine(1);
        ui->enableLine(2);
        ui->enableLine(3);

        ui->setLineTitle("Max SV" , 0, "Default: 10.0");
        ui->setLineTitle("Max BPM", 1, "Default: 1 000 000");
        ui->setLineTitle("Min SV" , 2, "Default: 0.1");
        ui->setLineTitle("Min BPM", 3, "Default: 0.0000001");

        ui->enableChkbx(0);
        ui->enableChkbx(1);

        ui->setChkbxTitle("Limit Settings");
        ui->setChkbxText("Limit SV" , 0);
        ui->setChkbxText("Limit BPM", 1);

        // Default these as checked
        ui->checkChkbx(0, true);
        ui->checkChkbx(1, true);

        break;
    };
}


cOM_TPList AAObj::applyEffect(cOM_TPList oldTPList)
{
    cOM_TPList newTPList,
               tempTPList;

    switch (objType)
    {
    case AAType::ADD_OFFSET     :
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.addOffset(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    case AAType::ADD_VALUE      :
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.addValue(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    case AAType::MULT_OFFSET    :
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.multiplyOffset(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    case AAType::MULT_VALUE     :
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.multiplyValue(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    case AAType::DEL_SV         :
        newTPList = oldTPList.splitByType(cOM_Common::TPFlag::BPM_ONLY);
        break;
    case AAType::DEL_BPM        :
        newTPList = oldTPList.splitByType(cOM_Common::TPFlag::SV_ONLY);
        break;
    case AAType::CONV_SV        :
        break;
    case AAType::CONV_BPM       :
        break;
    case AAType::ADD_TPLIST     :
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.addValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    case AAType::SUBTRACT_TPLIST:
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.subtractValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    case AAType::MULT_TPLIST    :
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.multiplyValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    case AAType::DIV_TPLIST     :
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.divideValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    case AAType::INVERT         :
        if (ui->getChkbxState(0) && ui->getChkbxState(1)) // SV & BPM
        {
            newTPList = oldTPList;
        } else if (!ui->getChkbxState(0) && ui->getChkbxState(1)) // BPM ONLY
        {
            newTPList = oldTPList.splitByType(cOM_Common::TPFlag::BPM_ONLY);
            tempTPList = oldTPList.splitByType(cOM_Common::TPFlag::SV_ONLY);
        } else // SV ONLY
        {
            newTPList = oldTPList.splitByType(cOM_Common::TPFlag::SV_ONLY);
            tempTPList = oldTPList.splitByType(cOM_Common::TPFlag::BPM_ONLY);
        }
        newTPList.subtractValue(ui->getLineText(0).toDouble());
        newTPList.multiplyValue(-1.0);
        newTPList.addValue(ui->getLineText(0).toDouble());
        newTPList.append(tempTPList);
        break;
    case AAType::LIMITVAL       :
        oldTPList.limitValues(ui->getLineText(0).toDouble(),
                              ui->getLineText(2).toDouble(),
                              ui->getLineText(1).toDouble(),
                              ui->getLineText(3).toDouble());
        newTPList = oldTPList;
        break;
    };

    return newTPList;
}

AAObj::AAType AAObj::getEffect()
{
    return objType;
}
QString AAObj::getEffectName(bool getInfo)
{
    QString name;
    switch (objType) // Get Name
    {
    case AAType::ADD_OFFSET     :
        name = "ADD_OFFSET";
        break;
    case AAType::ADD_VALUE      :
        name = "ADD_VALUE";
        break;
    case AAType::MULT_OFFSET    :
        name = "MULT_OFFSET";
        break;
    case AAType::MULT_VALUE     :
        name = "MULT_VALUE";
        break;
    case AAType::DEL_SV         :
        name = "DEL_SV";
        break;
    case AAType::DEL_BPM        :
        name = "DEL_BPM";
        break;
    case AAType::CONV_SV        :
        name = "CONV_SV";
        break;
    case AAType::CONV_BPM       :
        name = "CONV_BPM";
        break;
    case AAType::ADD_TPLIST     :
        name = "ADD_TPLIST";
        break;
    case AAType::SUBTRACT_TPLIST:
        name = "SUBTRACT_TPLIST";
        break;
    case AAType::MULT_TPLIST    :
        name = "MULT_TPLIST";
        break;
    case AAType::DIV_TPLIST     :
        name = "DIV_TPLIST";
        break;
    case AAType::INVERT         :
        name = "INVERT";
        break;
    case AAType::LIMITVAL       :
        name = "LIMITVAL";
        break;
    default:
        name = "";
        break;
    };
    if (getInfo){ // Get Info
        switch (objType)
        {
        case AAType::ADD_OFFSET     :
            qDebug() << "[Add Offset]" << "\n"
                     << "Offset (+ms): " << ui->getLineText(0) << "\n";
            break;
        case AAType::ADD_VALUE      :
            qDebug() << "[Add Value]" << "\n"
                     << "Value (+): " << ui->getLineText(0) << "\n";
            break;
        case AAType::MULT_OFFSET    :
            qDebug() << "[Multiply Offset]" << "\n"
                     << "Offset (*): " << ui->getLineText(0) << "\n";
            break;
        case AAType::MULT_VALUE     :
            qDebug() << "[Multiply Value]" << "\n"
                     << "Value (*): " << ui->getLineText(0) << "\n";
            break;
        case AAType::DEL_SV         :
            qDebug() << "[Delete SVs]" << "\n";
            break;
        case AAType::DEL_BPM        :
            qDebug() << "[Delete BPMs]" << "\n";
            break;
        case AAType::CONV_SV        :
            qDebug() << "[Convert to SV]" << "\n";
            break;
        case AAType::CONV_BPM       :
            qDebug() << "[Convert to BPM]" << "\n";
            break;
        case AAType::ADD_TPLIST     :
            qDebug() << "[Add TPList]" << "\n"
                     << "TPList: " << ui->getPTEText(0) << "\n";
            break;
        case AAType::SUBTRACT_TPLIST:
            qDebug() << "[Subtract TPList]" << "\n"
                     << "TPList: " << ui->getPTEText(0) << "\n";
            break;
        case AAType::MULT_TPLIST    :
            qDebug() << "[Multiply TPList]" << "\n"
                     << "TPList: " << ui->getPTEText(0) << "\n";
            break;
        case AAType::DIV_TPLIST     :
            qDebug() << "[Divide TPList]" << "\n"
                     << "TPList: " << "\n"
                     << ui->getPTEText(0).split("\n") << "\n";
            break;
        case AAType::INVERT         :
            qDebug() << "[Invert]" << "\n"
                     << "Axis: y = " << ui->getLineText(0) << "\n"
                     << "Invert SV: " << (ui->getChkbxState(0) ? "TRUE" : "FALSE")  << "\n"
                     << "Invert BPM: " << (ui->getChkbxState(1) ? "TRUE" : "FALSE") << "\n";
            break;
        case AAType::LIMITVAL       :
            qDebug() << "[Limit Values]" << "\n"
                     << "Max SV: "  << (ui->getLineText(0)) << "\n"
                     << "Max BPM: " << (ui->getLineText(1)) << "\n"
                     << "Min SV: "  << (ui->getLineText(2)) << "\n"
                     << "Min BPM: " << (ui->getLineText(3)) << "\n"
                     << "Limit SV: " << (ui->getChkbxState(0) ? "TRUE" : "FALSE")  << "\n"
                     << "Limit BPM: " << (ui->getChkbxState(1) ? "TRUE" : "FALSE") << "\n";
            break;
        default:
            qDebug() << "Invalid Effect." << "\n";
            break;
        };
    }
    return name;
}

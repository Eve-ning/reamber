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

void AAObj::setObjType(AAType newObjType)
{
    objType = newObjType;
}
void AAObj::setForm()
{
    // Reset everything to default
    setFormDefault();

    // Sets UI Form according to Object Type
    switch (objType.getIndex())
    {
    case 0: // Add Offset
    {
        ui->enableLine(0);
        ui->setLineTitle("Offset (+ms):", 0, "Insert Offset Here.");
        break;
    }
    case 1: // Add Value
    {
        ui->enableLine(0);
        ui->setLineTitle("Value (+):", 0, "Insert Value Here.");
        break;
    }
    case 2: // Multiply Offset
    {
        ui->enableLine(0);
        ui->setLineTitle("Value (*):", 0, "Insert Offset Here.");
        break;
    }
    case 3: // Multiply Value
    {
        ui->enableLine(0);
        ui->setLineTitle("Value (*):", 0, "Insert Value Here.");
        break;
    }
    case 4: // Delete SV
    {
        // No Form
        break;
    }
    case 5: // Delete BPM
    {
        // No Form
        break;
    }
    case 6: // Convert To SV
    {
        // No Form
        break;
    }
    case 7: // Convert To BPM
    {
        // No Form
        break;
    }
    case 8: // Add TPList
    {
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Add.>");
        break;
    }
    case 9: // Subtract TPList
    {
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Subtract.>");
        break;
    }
    case 10: // Multiply TPList
    {
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Multiply.>");
        break;
    }
    case 11: // Divide TPList
    {
        ui->enablePTE(0);
        ui->setPTETitle("Insert TP List", 0, "<Insert TP or TPList to Divide.>");
        break;
    }
    case 12: // Invert
    {
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
    }
    case 13: // Limit Values
    {
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
    }
    };
}


cOM_TPList AAObj::applyEffect(cOM_TPList oldTPList)
{
    cOM_TPList newTPList,
               tempTPList;

    // Add Offset
    // Add Value
    // Multiply Offset
    // Multiply Value
    // Delete SV
    // Delete BPM
    // Convert To SV
    // Convert To BPM
    // Add TPList
    // Subtract TPList
    // Multiply TPList
    // Divide TPList
    // Invert
    // Limit Values

    switch (objType.getIndex())
    {
    case 0: // Add Offset
    {
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.addOffset(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    }
    case 1: // Add Value
    {
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.addValue(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    }
    case 2: // Multiply Offset
    {
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.multiplyOffset(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    }
    case 3: // Multiply Value
    {
        if (!ui->getLineText(0).isEmpty())
        {
            oldTPList.multiplyValue(ui->getLineText(0).toDouble());
        }
        newTPList = oldTPList;
        break;
    }
    case 4: // Delete SV
    {
        newTPList = oldTPList.splitByType(cOM_Common::TPFlag::BPM_ONLY);
        break;
    }
    case 5: // Delete BPM
    {
        newTPList = oldTPList.splitByType(cOM_Common::TPFlag::SV_ONLY);
        break;
    }
    case 6: // Convert To SV
    {
        break;
    }
    case 7: // Convert To BPM
    {
        break;
    }
    case 8: // Add TPList
    {
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.addValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    }
    case 9: // Subtract TPList
    {
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.subtractValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    }
    case 10: // Multiply TPList
    {
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.multiplyValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    }
    case 11: // Divide TPList
    {
        if (!ui->getPTEText(0).isEmpty())
        {
            oldTPList.divideValue(cOM_TPList(ui->getPTEText(0)));
        }
        newTPList = oldTPList;
        break;
    }
    case 12: // Invert
    {
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
    }
    case 13: // Limit Values
    {
        oldTPList.limitValues(ui->getLineText(0).toDouble(),
                              ui->getLineText(2).toDouble(),
                              ui->getLineText(1).toDouble(),
                              ui->getLineText(3).toDouble());
        newTPList = oldTPList;
        break;
    }
    };

    return newTPList;
}

AAType AAObj::getEffect()
{
    return objType;
}
QString AAObj::getEffectName(bool getInfo)
{
    QString name;
    name = objType.getName();

 // Add Offset
 // Add Value
 // Multiply Offset
 // Multiply Value
 // Delete SV
 // Delete BPM
 // Convert To SV
 // Convert To BPM
 // Add TPList
 // Subtract TPList
 // Multiply TPList
 // Divide TPList
 // Invert
 // Limit Values

    if (getInfo){ // Get Info
        switch (objType.getIndex())
        {
        case 0: // Add Offset
        {
            qDebug() << "[Add Offset]" << "\n"
                     << "Offset (+ms): " << ui->getLineText(0) << "\n";
            break;
        }
        case 1: // Add Value
        {
            qDebug() << "[Add Value]" << "\n"
                     << "Value (+): " << ui->getLineText(0) << "\n";
            break;
        }
        case 2: // Multiply Offset
        {
            qDebug() << "[Multiply Offset]" << "\n"
                     << "Offset (*): " << ui->getLineText(0) << "\n";
            break;
        }
        case 3: // Multiply Value
        {
            qDebug() << "[Multiply Value]" << "\n"
                     << "Value (*): " << ui->getLineText(0) << "\n";
            break;
        }
        case 4: // Delete SV
        {
            qDebug() << "[Delete SVs]" << "\n";
            break;
        }
        case 5: // Delete BPM
        {
            qDebug() << "[Delete BPMs]" << "\n";
            break;
        }
        case 6: // Convert To SV
        {
            qDebug() << "[Convert to SV]" << "\n";
            break;
        }
        case 7: // Convert To BPM
        {
            qDebug() << "[Convert to BPM]" << "\n";
            break;
        }
        case 8: // Add TPList
        {
            qDebug() << "[Add TPList]" << "\n"
                     << "TPList: " << ui->getPTEText(0) << "\n";
            break;
        }
        case 9: // Subtract TPList
        {
            qDebug() << "[Subtract TPList]" << "\n"
                     << "TPList: " << ui->getPTEText(0) << "\n";
            break;
        }
        case 10: // Multiply TPList
        {
            qDebug() << "[Multiply TPList]" << "\n"
                     << "TPList: " << ui->getPTEText(0) << "\n";
            break;
        }
        case 11: // Divide TPList
        {
            qDebug() << "[Divide TPList]" << "\n"
                     << "TPList: " << "\n"
                     << ui->getPTEText(0).split("\n") << "\n";
            break;
        }
        case 12: // Invert
        {
            qDebug() << "[Invert]" << "\n"
                     << "Axis: y = " << ui->getLineText(0) << "\n"
                     << "Invert SV: " << (ui->getChkbxState(0) ? "TRUE" : "FALSE")  << "\n"
                     << "Invert BPM: " << (ui->getChkbxState(1) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case 13: // Limit Values
        {
            qDebug() << "[Limit Values]" << "\n"
                     << "Max SV: "  << (ui->getLineText(0)) << "\n"
                     << "Max BPM: " << (ui->getLineText(1)) << "\n"
                     << "Min SV: "  << (ui->getLineText(2)) << "\n"
                     << "Min BPM: " << (ui->getLineText(3)) << "\n"
                     << "Limit SV: " << (ui->getChkbxState(0) ? "TRUE" : "FALSE")  << "\n"
                     << "Limit BPM: " << (ui->getChkbxState(1) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        default:
        {
            qDebug() << "Invalid Effect." << "\n";
            break;
        }
        };
    }
    return name;
}

// FOR AATYPE
const QStringList AAType::nameList
{
    "Add Offset",      /* ADD_OFFSET      */
    "Add Value",       /* ADD_VALUE       */
    "Multiply Offset", /* MULT_OFFSET     */
    "Multiply Value",  /* MULT_VALUE      */
    "Delete SV",       /* DEL_SV          */
    "Delete BPM",      /* DEL_BPM         */
    "Convert To SV",   /* CONV_SV         */
    "Convert To BPM",  /* CONV_BPM        */
    "Add TPList",      /* ADD_TPLIST      */
    "Subtract TPList", /* SUBTRACT_TPLIST */
    "Multiply TPList", /* MULT_TPLIST     */
    "Divide TPList",   /* DIV_TPLIST      */
    "Invert",          /* INVERT          */
    "Limit Values"     /* LIMITVAL        */
};

void AAType::load(QString newName)
{
    if (!nameList.contains(newName))
    {
        qDebug() << __FUNCTION__ << "Failed to load via name.";
        return;
    }
    name = newName;
}
void AAType::load(int newIndex)
{
    if (newIndex >= nameList.length())
    {
        qDebug() << __FUNCTION__ << "Index out of range.";
        return;
    }
    name = nameList[newIndex];
}

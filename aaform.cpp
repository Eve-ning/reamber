#include "aaform.h"
#include "ui_aaform.h"

AAForm::AAForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AAForm)
{
    ui->setupUi(this);
}

AAForm::~AAForm()
{
    delete ui;
}

bool AAForm::disableAll()
{
    return
    disableChkbx()        ||
    disableLine()         ||
    disablePTE()          ||
    disableRadio();
}
bool AAForm::enableAll()
{
    return
    enableChkbx()         ||
    enableLine()          ||
    enablePTE()           ||
    enableRadio();
}

bool AAForm::disableChkbx(int index)
{
    if (index >= 0)
    {
        switch (index) {
        case 0:
            ui->chkbx_0->setEnabled(false);
            ui->chkbx_0->setChecked(false);
            break;
        case 1:
            ui->chkbx_1->setEnabled(false);
            ui->chkbx_1->setChecked(false);
            break;
        case 2:
            ui->chkbx_2->setEnabled(false);
            ui->chkbx_2->setChecked(false);
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }

        // CHECK IF ANY ARE ENABLED, IF SO THEN SET IN USE
        if (ui->chkbx_0->isEnabled() ||
            ui->chkbx_1->isEnabled() ||
            ui->chkbx_2->isEnabled())
        {
            ui->chkbxGrp->setTitle("In Use");
        }
        else
        {
            ui->chkbxGrp->setTitle("Unused");
        }
    }
    else
    {
        ui->chkbxGrp->setTitle("Unused");

        ui->chkbx_0->setEnabled(false);
        ui->chkbx_1->setEnabled(false);
        ui->chkbx_2->setEnabled(false);

        ui->chkbx_0->setChecked(false);
        ui->chkbx_1->setChecked(false);
        ui->chkbx_2->setChecked(false);
    }

    return true;
}
bool AAForm::enableChkbx (int index)
{
    if (index >= 0)
    {
        switch (index) {
        case 0:
            ui->chkbx_0->setEnabled(false);
            ui->chkbx_0->setChecked(false);
            break;
        case 1:
            ui->chkbx_1->setEnabled(false);
            ui->chkbx_1->setChecked(false);
            break;
        case 2:
            ui->chkbx_2->setEnabled(false);
            ui->chkbx_2->setChecked(false);
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }

        // CHECK IF ANY ARE ENABLED, IF SO THEN SET IN USE
        if (ui->chkbx_0->isEnabled() ||
            ui->chkbx_1->isEnabled() ||
            ui->chkbx_2->isEnabled())
        {
            ui->chkbxGrp->setTitle("In Use");
        }
        else
        {
            ui->chkbxGrp->setTitle("Unused");
        }
    }
    else
    {
        ui->chkbxGrp->setTitle("In Use");

        ui->chkbx_0->setEnabled(true);
        ui->chkbx_1->setEnabled(true);
        ui->chkbx_2->setEnabled(true);
    }

    return true;
}
bool AAForm::disableLine (int index)
{
    if (index >= 0)
    {
        switch (index) {
        case 0:
            ui->lineGrp_0->setTitle("Unused");
            ui->line_0->setEnabled(false);
            ui->line_0->clear();
            break;
        case 1:
            ui->lineGrp_1->setTitle("Unused");
            ui->line_1->setEnabled(false);
            ui->line_1->clear();
            break;
        case 2:
            ui->lineGrp_2->setTitle("Unused");
            ui->line_2->setEnabled(false);
            ui->line_2->clear();
            break;
        case 3:
            ui->lineGrp_3->setTitle("Unused");
            ui->line_3->setEnabled(false);
            ui->line_3->clear();
            break;
        case 4:
            ui->lineGrp_4->setTitle("Unused");
            ui->line_4->setEnabled(false);
            ui->line_4->clear();
            break;
        case 5:
            ui->lineGrp_5->setTitle("Unused");
            ui->line_5->setEnabled(false);
            ui->line_5->clear();
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->lineGrp_0->setTitle("Unused");
        ui->lineGrp_1->setTitle("Unused");
        ui->lineGrp_2->setTitle("Unused");
        ui->lineGrp_3->setTitle("Unused");
        ui->lineGrp_4->setTitle("Unused");
        ui->lineGrp_5->setTitle("Unused");

        ui->line_0->setEnabled(false);
        ui->line_1->setEnabled(false);
        ui->line_2->setEnabled(false);
        ui->line_3->setEnabled(false);
        ui->line_4->setEnabled(false);
        ui->line_5->setEnabled(false);

        ui->line_0->clear();
        ui->line_1->clear();
        ui->line_2->clear();
        ui->line_3->clear();
        ui->line_4->clear();
        ui->line_5->clear();
    }

    return true;
}
bool AAForm::enableLine  (int index)
{
    if (index >= 0)
    {
        switch (index) {
        case 0:
            ui->lineGrp_0->setTitle("In Use");
            ui->line_0->setEnabled(true);
            ui->line_0->clear();
            break;
        case 1:
            ui->lineGrp_1->setTitle("In Use");
            ui->line_1->setEnabled(true);
            ui->line_1->clear();
            break;
        case 2:
            ui->lineGrp_2->setTitle("In Use");
            ui->line_2->setEnabled(true);
            ui->line_2->clear();
            break;
        case 3:
            ui->lineGrp_3->setTitle("In Use");
            ui->line_3->setEnabled(true);
            ui->line_3->clear();
            break;
        case 4:
            ui->lineGrp_4->setTitle("In Use");
            ui->line_4->setEnabled(true);
            ui->line_4->clear();
            break;
        case 5:
            ui->lineGrp_5->setTitle("In Use");
            ui->line_5->setEnabled(true);
            ui->line_5->clear();
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->lineGrp_0->setTitle("In Use");
        ui->lineGrp_1->setTitle("In Use");
        ui->lineGrp_2->setTitle("In Use");
        ui->lineGrp_3->setTitle("In Use");
        ui->lineGrp_4->setTitle("In Use");
        ui->lineGrp_5->setTitle("In Use");

        ui->line_0->setEnabled(true);
        ui->line_1->setEnabled(true);
        ui->line_2->setEnabled(true);
        ui->line_3->setEnabled(true);
        ui->line_4->setEnabled(true);
        ui->line_5->setEnabled(true);

        ui->line_0->clear();
        ui->line_1->clear();
        ui->line_2->clear();
        ui->line_3->clear();
        ui->line_4->clear();
        ui->line_5->clear();
    }

    return true;
}
bool AAForm::disablePTE  (int index)
{
    if (index >= 0)
    {
        switch (index)
        {
        case 0:
            ui->pteGrp->setTitle("Unused");
            ui->pte->setEnabled(false);
            ui->pte->clear();
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->pteGrp->setTitle("Unused");

        ui->pte->setEnabled(false);

        ui->pte->clear();
    }

    return true;
}
bool AAForm::enablePTE   (int index)
{
    if (index >= 0)
    {
        switch (index)
        {
        case 0:
            ui->pteGrp->setTitle("In Use");
            ui->pte->setEnabled(true);
            ui->pte->clear();
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->pteGrp->setTitle("In Use");

        ui->pte->setEnabled(true);

        ui->pte->clear();
    }
    return true;
}
bool AAForm::disableRadio(int index)
{
    if (index >= 0)
    {
        switch (index)
        {
        case 0:
            ui->radioGrp->setTitle("In Use");
            ui->radio_0->setEnabled(true);
            ui->radio_0->setChecked(false);
            break;
        case 1:
            ui->radioGrp->setTitle("In Use");
            ui->radio_1->setEnabled(true);
            ui->radio_1->setChecked(false);
            break;
        case 2:
            ui->radioGrp->setTitle("In Use");
            ui->radio_2->setEnabled(true);
            ui->radio_2->setChecked(false);
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->radioGrp->setTitle("Unused");

        ui->radio_0->setEnabled(false);
        ui->radio_1->setEnabled(false);
        ui->radio_2->setEnabled(false);

        ui->radio_0->setChecked(false);
        ui->radio_1->setChecked(false);
        ui->radio_2->setChecked(false);
    }
    return true;
}
bool AAForm::enableRadio (int index)
{
    if (index >= 0)
    {
        switch (index)
        {
        case 0:
            ui->radioGrp->setTitle("Unused");
            ui->radio_0->setEnabled(false);
            ui->radio_2->setChecked(false);
            break;
        case 1:
            ui->radioGrp->setTitle("Unused");
            ui->radio_1->setEnabled(false);
            ui->radio_2->setChecked(false);
            break;
        case 2:
            ui->radioGrp->setTitle("Unused");
            ui->radio_2->setEnabled(false);
            ui->radio_2->setChecked(false);
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->radioGrp->setTitle("Unused");

        ui->radio_0->setEnabled(false);
        ui->radio_1->setEnabled(false);
        ui->radio_2->setEnabled(false);

        ui->radio_0->setChecked(false);
        ui->radio_1->setChecked(false);
        ui->radio_2->setChecked(false);
    }
    return true;
}

bool AAForm::setChkbxTitle(QString newTitle)
{
    ui->chkbxGrp->setTitle(newTitle);
}
bool AAForm::setChkbxText (QString newText , int index)
{
    switch (index) {
    case 0:
        ui->chkbx_0->setText(newText);
        break;
    case 1:
        ui->chkbx_1->setText(newText);
        break;
    case 2:
        ui->chkbx_2->setText(newText);
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return false;
    }

    return true;
}
bool AAForm::setLineTitle (QString newTitle, int index,  QString hintText)
{
    switch (index) {
    case 0:
        ui->lineGrp_0->setTitle(newTitle);
        ui->line_0->setPlaceholderText(hintText);
        break;
    case 1:
        ui->lineGrp_1->setTitle(newTitle);
        ui->line_1->setPlaceholderText(hintText);
        break;
    case 2:
        ui->lineGrp_2->setTitle(newTitle);
        ui->line_2->setPlaceholderText(hintText);
        break;
    case 3:
        ui->lineGrp_3->setTitle(newTitle);
        ui->line_3->setPlaceholderText(hintText);
        break;
    case 4:
        ui->lineGrp_4->setTitle(newTitle);
        ui->line_4->setPlaceholderText(hintText);
        break;
    case 5:
        ui->lineGrp_5->setTitle(newTitle);
        ui->line_5->setPlaceholderText(hintText);
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return false;
    }

    return true;
}
bool AAForm::setPTETitle  (QString newTitle, int index,  QString hintText)
{
    switch (index) {
    case 0:
        ui->pteGrp->setTitle(newTitle);
        ui->pte->setPlaceholderText(hintText);
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return false;
    }

    return true;
}
bool AAForm::setRadioTitle(QString newTitle)
{
    ui->radioGrp->setTitle(newTitle);
}
bool AAForm::setRadioText (QString newText , int index)
{
    switch (index) {
    case 0:
        ui->radio_0->setText(newText);
        break;
    case 1:
        ui->radio_1->setText(newText);
        break;
    case 2:
        ui->radio_2->setText(newText);
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return false;
    }

    return true;
}

bool AAForm::getChkbxState(int index)
{
    switch (index) {
    case 0:
        return ui->chkbx_0->isChecked();
        break;
    case 1:
        return ui->chkbx_1->isChecked();
        break;
    case 2:
        return ui->chkbx_2->isChecked();
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return false;
    }
}
QString AAForm::getLineText(int index)
{
    switch (index) {
    case 0:
        return ui->line_0->text();
        break;
    case 1:
        return ui->line_1->text();
        break;
    case 2:
        return ui->line_2->text();
        break;
    case 3:
        return ui->line_3->text();
        break;
    case 4:
        return ui->line_4->text();
        break;
    case 5:
        return ui->line_5->text();
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return "";
    }
}
QString AAForm::getPTEText(int index)
{
    switch (index) {
    case 0:
        return ui->pte->toPlainText();
        break;
    default:
        qDebug() << __FUNCTION__ << "Out of Index: " << index;
        return "";
    }
}
bool AAForm::getRadioState(int index)
{
    switch (index) {
    case 0:
        return ui->radio_0->isChecked();
        break;
    case 1:
        return ui->radio_1->isChecked();
        break;
    case 2:
        return ui->radio_2->isChecked();
        break;
    }
}

bool AAForm::checkChkbx(int index, bool check)
{
    if (index >= 0)
    {
        switch (index) {
        case 0:
            ui->chkbx_0->setChecked(check);
            break;
        case 1:
            ui->chkbx_1->setChecked(check);
            break;
        case 2:
            ui->chkbx_2->setChecked(check);
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->chkbx_0->setChecked(check);
        ui->chkbx_1->setChecked(check);
        ui->chkbx_2->setChecked(check);
    }

    return true;
}
bool AAForm::checkRadio(int index, bool check)
{
    if (index >= 0)
    {
        switch (index) {
        case 0:
            ui->radio_0->setChecked(check);
            break;
        case 1:
            ui->radio_1->setChecked(check);
            break;
        case 2:
            ui->radio_2->setChecked(check);
            break;
        default:
            qDebug() << __FUNCTION__ << "Out of Index: " << index;
            return false;
        }
    }
    else
    {
        ui->radio_0->setChecked(check);
        ui->radio_1->setChecked(check);
        ui->radio_2->setChecked(check);
    }

    return true;
}















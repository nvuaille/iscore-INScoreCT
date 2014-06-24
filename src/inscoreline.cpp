#include "inscoreline.h"
#include "ui_inscoreline.h"

/* ************************************************
 * ctor & dtor
 * ************************************************/

INScoreLine::INScoreLine(int _index, QWidget *parent) :
    QWidget(parent), index(_index),
    ui(new Ui::INScoreLine)
{
    ui->setupUi(this);
}

INScoreLine::~INScoreLine()
{
    delete ui;
}

/* ************************************************
 * get methods
 * ************************************************/
// name
QString INScoreLine::objectName()
{
    return ui->nameLine->text();
}

// path
QString INScoreLine::objectPath()
{
    return ui->pathLine->text();
}

// is to create
bool INScoreLine::isToCreate()
{
    return ui->toCreateButton->isChecked();
}

// selected type
QString INScoreLine::selectedType()
{
    return ui->typeList->currentText();
}

// selected parameter
QString INScoreLine::selectedParameter(int _i)
{
    auto param = qobject_cast<QCheckBox*>(ui->parametersBox->children().value(_i));
    return param->text();
}

// parameter state
bool INScoreLine::parameterValue(string _name)
{
    return ui->parametersBox->findChild<QCheckBox *>(_name.c_str())->isChecked();
}

QString INScoreLine::getCreationValue()
{
    QString value = ui->creationValue->text();
    if(fileObject||textObject) {
        value = QString("\"") + value + QString("\"");
    }
    return value;
}

// nb checkboxes = nb parameters
int INScoreLine::nbCheckBoxes()
{
    return int(ui->parametersBox->children().size());
}

// SET METHOD

void INScoreLine::setLine(INScoreObject *_object)
{
    ui->nameLine->setText(_object->getName().c_str());
    ui->pathLine->setText(_object->getPath().c_str());
    string boxName = "";
    for(int i(0); i<nbCheckBoxes(); ++i) {
        boxName = _object->getParameterName(i);
        ui->parametersBox->findChild<QCheckBox *>(boxName.c_str())->setChecked(_object->isParameterChecked(i));
    }
}

/* ************************************************
 * slots
 * ************************************************/

// create button en/dis-ables type list
void INScoreLine::on_toCreateButton_toggled(bool checked)
{
    ui->typeList->setEnabled(checked);
    ui->creationValue->setEnabled(checked);
}

// fill in path
void INScoreLine::on_nameLine_textChanged(const QString &arg1)
{
    ui->pathLine->setText(QString("/ITL/scene/") + arg1);
    if(ui->nameLine->text().isEmpty()) {
        ui->toCreateButton->setChecked(false);
        ui->toCreateButton->setEnabled(false);
    }
    else {
        ui->toCreateButton->setEnabled(true);
    }
}

// en/dis-ables parameter following the object type
void INScoreLine::on_typeList_currentIndexChanged(int index)
{
    int i = 0;
    while(i < int(ui->parametersBox->children().size())) {
        auto box = qobject_cast<QCheckBox*>(ui->parametersBox->children().value(i));
        box->setEnabled(true);
        ++i;
    }
    ui->signal->setChecked(false);
    ui->signal->setEnabled(false);
    ui->creationValue->setEnabled(true);
    fileObject = false;
    textObject = false;

    switch (index)
    {
        case 1: // curve
            ui->size->setEnabled(false);
            ui->size->setChecked(false);
            break;

        case 3: // fastgraph
            ui->signal->setEnabled(true);
            ui->creationValue->setEnabled(false);
            ui->creationValue->setText("");
            break;

        case 4: // file
            ui->size->setEnabled(false);
            ui->size->setChecked(false);
            loadFileName();
            break;

        case 5: // gmnf
            ui->size->setEnabled(false);
            ui->size->setChecked(false);
            loadFileName();
            break;

        case 6: // graph
            ui->signal->setEnabled(true);
            ui->creationValue->setEnabled(false);
            ui->creationValue->setText("");
            break;

        case 7: // grid
            ui->size->setEnabled(false);
            ui->size->setChecked(false);
            break;

        case 10: // line xy
            ui->size->setEnabled(false);
            ui->size->setChecked(false);
            break;

        case 11: // polygon
            ui->size->setEnabled(false);
            ui->size->setChecked(false);
            break;

        case 13: // svgf
            ui->size->setEnabled(false);
            ui->color->setEnabled(false);
            ui->dcolor->setEnabled(false);
            ui->color->setChecked(false);
            ui->dcolor->setChecked(false);
            loadFileName();
            break;

        case 14: // text
            ui->size->setEnabled(false);
            textObject = true;
            break;

        default :
            break;
    }
}

void INScoreLine::on_removeButton_clicked()
{
    int del = QMessageBox::question(this, "Delete line", "Do you really want to delete this line ?", QMessageBox::Yes | QMessageBox::No);
    if(del == QMessageBox::Yes) {
        emit removeLine(index);
        this->close();
    }
}

void INScoreLine::loadFileName()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QString("../../.."));
    ui->creationValue->setText(fileName);
    fileObject = true;
}

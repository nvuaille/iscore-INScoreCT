#include "../headers/advancedoptions.h"
#include "ui_advancedoptions.h"

AdvancedOptions::AdvancedOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedOptions)
{
    ui->setupUi(this);
    this->setWindowTitle("Advanced Options");


}

AdvancedOptions::~AdvancedOptions()
{
    delete ui;
}

void AdvancedOptions::displayInitValues(INScoreObject *object)
{
    ui->red->setValue(object->getInitValue("red"));
    ui->green->setValue(object->getInitValue("green"));
    ui->blue->setValue(object->getInitValue("blue"));
    ui->alpha->setValue(object->getInitValue("alpha"));

    ui->x->setValue(object->getInitValue("x"));
    ui->y->setValue(object->getInitValue("y"));
    ui->z->setValue(object->getInitValue("z"));
    ui->xorigin->setValue(object->getInitValue("xorigin"));
    ui->yorigin->setValue(object->getInitValue("yorigin"));
    ui->angle->setValue(object->getInitValue("angle"));
    ui->scale->setValue(object->getInitValue("scale"));
    currentObject = object;
}


void AdvancedOptions::on_ok_clicked()
{
    currentObject->setInitValue("red", ui->red->value());
    currentObject->setInitValue("green", ui->green->value());
    currentObject->setInitValue("blue", ui->blue->value());
    currentObject->setInitValue("alpha", ui->alpha->value());

    currentObject->setInitValue("x", ui->x->value());
    currentObject->setInitValue("y", ui->y->value());
    currentObject->setInitValue("z", ui->z->value());
    currentObject->setInitValue("xorigin", ui->xorigin->value());
    currentObject->setInitValue("yorigin", ui->yorigin->value());
    currentObject->setInitValue("angle", ui->angle->value());
    currentObject->setInitValue("scale", ui->scale->value());

    this->close();
}

void AdvancedOptions::on_cancel_clicked()
{
    this->close();
}

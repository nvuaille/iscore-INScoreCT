#ifndef ADVANCEDOPTIONS_H
#define ADVANCEDOPTIONS_H

#include <QDialog>
#include "inscoreobject.h"
#include <iostream>

namespace Ui {
class AdvancedOptions;
}

class AdvancedOptions : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedOptions(QWidget *parent = 0);
    ~AdvancedOptions();

    void displayInitValues(INScoreObject * object);

signals:
    void saveOptions();

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::AdvancedOptions *ui;
    INScoreObject *currentObject;
};

#endif // ADVANCEDOPTIONS_H

#ifndef INSCORELINE_H
#define INSCORELINE_H

#include <QtGui>
#include <QWidget>
#include <iostream>
#include "inscoreobject.h"

namespace Ui {
class INScoreLine;
}

class INScoreLine : public QWidget
{
    Q_OBJECT

public:
    explicit INScoreLine(int _index, QWidget *parent = 0);
    ~INScoreLine();

    /* ***************************************************
     * GET METHODS
     * **************************************************/
    QString objectName();
    QString objectPath();
    bool isToCreate();
    QString selectedType();
    QString selectedParameter(int _i);
    bool parameterValue(string _name);
    QString getCreationValue();

    int nbCheckBoxes();
    void setLine(INScoreObject *_object);

signals:
    void removeLine(const int lineIndex);
    void advancedOptions(const int lineIndex);

private slots:
    /* ***************************************************
     * SLOTS
     * **************************************************/

    // create button en/dis-ables type list
    void on_toCreateButton_toggled(bool checked);

    // change name auto fill in path
    void on_nameLine_textChanged(const QString &arg1);

    // dis- or en-ables the checkboxes, in accordance with selected type
    void on_typeList_currentIndexChanged(int index);

    // remove the current line
    void on_removeButton_clicked();

    void on_options_clicked();

private:
    const int index;
    Ui::INScoreLine *ui;
    bool fileObject;
    bool textObject;
    void loadFileName();
};

#endif // INSCORELINE_H

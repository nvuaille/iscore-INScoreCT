#ifndef INSCOREDATA_H
#define INSCOREDATA_H

#include<QWidget>
#include<QtGui>
#include<String>
#include<QString>
#include"inscoreobject.h"
#include "xmldata.h"

class INScoreData : public QWidget
{

public:
    INScoreData();
    ~INScoreData();

    void addObject(const int index);
    void removeObject(const int index);
    void generateSetup();
    void generateAliases();
    void writeFiles(QString filePath);

    map<int, INScoreObject *> *getList();
    INScoreObject *getObject(const int index);

private:
    QString setup;
    QString aliases;
    QString fileName;
    map<int, INScoreObject*> objectList;

    QString extractProjectName(QString projectPath);
};

#endif // INSCOREDATA_H

#ifndef INSCOREDATA_H
#define INSCOREDATA_H

#include<QWidget>
#include<QtGui>
#include<string>
#include<QString>
#include"inscoreobject.h"
#include "xmldata.h"

/* **************************************************
 * Class container : list of INScoreObject
 * Used to create the INScore configuration files
 * **************************************************/

class INScoreData : public QWidget
{

public:
    INScoreData();
    ~INScoreData();

    /* *********************************************
     * add a new object in the list
     * *********************************************/
    void addObject(const int index);

    /* *********************************************
     * add an existing object in the list
     * *********************************************/
    void addObject(const int index, const INScoreObject &_copy);

    /* *********************************************
     * remove an object from the list
     * *********************************************/
    void removeObject(const int index);

    /* *********************************************
     * generate the setup file content as string
     * *********************************************/
    void generateSetup();

    /* *********************************************
     * generate the aliases file content as string
     * *********************************************/
    void generateAliases();

    /* *********************************************
     * write the strings into files
     * *********************************************/
    void writeFiles(QString filePath);

    map<int, INScoreObject *> *getList();
    INScoreObject *getObject(const int index);

private:
    /* string that contain setup */
    QString setup;
    /* string that contain aliases */
    QString aliases;
    /* string that contain the project name */
    QString fileName;

    /* objects list */
    map<int, INScoreObject*> objectList;

    /* extract name from path */
    QString extractProjectName(QString projectPath);
};

#endif // INSCOREDATA_H

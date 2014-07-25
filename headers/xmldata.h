#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <QtGui>
#include <QtXml>
#include <QWidget>
#include <QMessageBox>
#include <vector>
#include "inscoreobject.h"
#include "parameter.h"
#include <string>
#include <iostream>


using namespace std;

/* ***************************************************
 * This class setup a QDomDocument from a vector of
 * INScoreObject
 * and writes it into a xml file
 * ***************************************************/

class XmlData : public QWidget
{

public:
    /* ***************************************************
     * contains declaration of all variables attributes
     * fill in the parameters vector
     * ***************************************************/
    XmlData();
    ~XmlData();

    /* ***************************************************
     * Read a ".conf" file and load it in a DOM object
     * ***************************************************/
    void readFile(QString _file);

    /* ***************************************************
     * writes the xml document into a file
     * ***************************************************/
    void writeFile(QString _fileName);

    /* ***************************************************
     * generates the xml DOM that describe the OSC tree
     * it takes informations from objectList
     * ***************************************************/
    void generateOSCTree(map<int, INScoreObject *> *_objectList);

    /* ***************************************************
     * generate a xml DOM that contain all informations
     * needed to edit a previous work
     * ***************************************************/
    void generateSaveFile(map<int, INScoreObject *> *_objectList);

    /* ***************************************************
     * fill in the INScore Object list with informations
     * from the DOM object.
     * ***************************************************/
    void xmlToInscoreObject();

    INScoreObject * getObject(int index);

    int getNbParameters();
    Parameter *getParameter(int _i);

    int nbInscoreObject();

private:
    /* ***************************************************
     * create a xml node, that contain others
     * ***************************************************/
    QDomElement newContainerElement(string _name, string _tag);

    /* object that contain all the xml informations */
    QDomDocument *domDoc;

    /* list all enabled parameters */
    vector<Parameter*> parameters;

    /* the object list */
    map<int, INScoreObject *> inscoreObjectList;

};

#endif // XML_DOM_H

#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <QtGui>
#include <QtXml>
#include <QWidget>
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
     * a revoir
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
    void generateXML(map<int, INScoreObject *> *_objectList);
    void xmlToInscoreObject();

    INScoreObject * getObject(int index);

    int getNbParameters();
    Parameter *getParameter(int _i);

    int nbInscoreObject();

private:
    /* ***************************************************
     * creates a xml node, that contain others
     * ***************************************************/
    QDomElement newContainerElement(string _name, string _tag);

    /* object that contain all the xml informations */
    QDomDocument domDoc;

    /* list all enabled parameters */
    vector<Parameter*> parameters;

    map<int, INScoreObject *> inscoreObjectList;

};

#endif // XML_DOM_H

#include "../headers/inscoredata.h"

INScoreData::INScoreData()
{
}

INScoreData::~INScoreData()
{

}

void INScoreData::addObject(const int index)
{
    objectList[index] = new INScoreObject();
}

void INScoreData::addObject(const int index, const INScoreObject &_copy)
{
    objectList[index] = new INScoreObject();
    objectList[index]->setInitValues(_copy.getInitValues());
}

void INScoreData::removeObject(const int index)
{
    if(objectList.find(index) != objectList.end()) {
        objectList.erase(index);
    }
}

void INScoreData::generateSetup()
{
    /* ******************************************
     *      OSC address has following form :
     *
     * /scene/objectName/parameter/variable
     *
     * we want to write :
     * 'INScorePath' alias 'OSCaddress' 'method'
     *
     * where method is (here) equal to "variable"
     *
     ********************************************/

    setup.clear();
    setup = "! This file contains the init value for the INScore object \n";
    setup = setup + "! You can adjust it at your will \n";
    setup = setup + "!  ************************************************************** \n \n";

    if(objectList.empty()) {
        QMessageBox::critical(NULL,"Error","Nothing to generate !");
        return;
    }
    map<int, INScoreObject*>::iterator pairIt= objectList.begin();

    while(pairIt!=objectList.end())
    {
        INScoreObject * it(pairIt->second);
        string inscoreAddress = (it)->getPath();
        string reAllocateSignal = string("/ITL/") + (it)->getScene() + string(" watch+ endPaint ("); // watch for new value for a signal to draw it in the graph
        if((it)->getToCreate()) {
            /* Rules for graph element : building signals */
            if((it)->getType().compare("graph") == 0) {
                string signalPath = string("/ITL/") + (it)->getScene() + "/signal" ;
                string setSignal = signalPath + "/" + (it)->getCreationValue() + " set ";
                int k = 0;
                while(k< (it)->getSignalSize())
                {
                    QString inscoreSignalAdress = QString((signalPath + "/" + (it)->getSignal(k) + (it)->getName()).c_str());
                    setup = setup + inscoreSignalAdress + QString((" size " + (it)->getBufferSize(k) + "; \n").c_str());
                    setup = setup + inscoreSignalAdress + QString((" default " + (it)->getSignalValue(k) + "; \n").c_str());
                    aliases = aliases + inscoreSignalAdress + QString((" alias \"/" + (it)->getScene() + "/" + (it)->getName() + "/signal/" + (it)->getSignal(k) + "\"; \n").c_str());
                    setSignal = setSignal + (it)->getSignal(k) + (it)->getName() +  " ";
                    ++k;
                }
                // set signal : set y t h s b a
                setup = setup + QString((setSignal + "; \n").c_str());
                // add a watch command to display new value
                setup = setup + QString((reAllocateSignal + inscoreAddress + " set " + (it)->getType() + " " + (it)->getCreationValue() + "); \n").c_str());
            }
            /* Setup for all new element */
            setup = setup + QString(it->getInitCommand().c_str());
            setup = setup + QString((inscoreAddress + " show 0;" + "\n").c_str());

        }
        setup = setup + QString("\n");
        ++pairIt;
    }
    setup = setup + "/ITL load \"" + fileName + "-alias.inscore\"; \n";

}

void INScoreData::generateAliases()
{
    aliases.clear();

    aliases = "! This file contains aliases instruction for INScore \n";
    aliases = aliases + "! It has to be conform with the i-score OSC tree (.xml) \n";
    aliases = aliases + "! in a normal use, you DON'T have to MODIFY this file \n";
    aliases = aliases + "! ************************************************************** \n \n";

    XmlData *dom;
    dom = new XmlData();
    string inscoreAddress = "";
    string signal = "signal";

    map<int, INScoreObject*>::iterator pairIt= objectList.begin();
    while(pairIt!=objectList.end())
    {
        INScoreObject * it(pairIt->second);
        string OSCaddress = string("\"/") + (it)->getScene() + "/" + (it)->getName() + "/"; // OSC address for an object
        int i = 0;
        string method = "";
        /* creating aliases for all parameter */
        while(i<dom->getNbParameters()) {
            string currentParam = dom->getParameter(i)->getParameterName();
            if((it)->isParameterChecked(currentParam)) {
                string OSCparamAddress = OSCaddress ; // loop to add each parameter

                if(i!=0) { // show variable isn't in a parameter
                    OSCparamAddress = OSCparamAddress + currentParam + "/";
                }

                int j = 0;
                while(j<dom->getParameter(i)->getNbVariable()) {
                    inscoreAddress = (it)->getPath();
                    method = dom->getParameter(i)->getVariable(j).getVariableName();
                    if(signal.compare(dom->getParameter(i)->getParameterName()) != 0) {
                        string OSCfinalAddress = OSCparamAddress + dom->getParameter(i)->getVariable(j).getVariableName() + "\""; // loop to add each variable
                        aliases = aliases + QString((inscoreAddress + " alias " + OSCfinalAddress + " " + method + ";" + "\n").c_str()); // and write
                    }
                    j++;
                }
            }
            i++;
        }
        aliases = aliases +  QString("\n");
        ++pairIt;
    }
    delete dom;
}

void INScoreData::writeFiles(QString filePath)
{
    fileName = extractProjectName(filePath);

    generateAliases();
    generateSetup();

    /* write the 2 inscore files */
    QString setupPath = filePath + "-setup.inscore";
    QFile setupFile(setupPath);
    setupFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream setupStream(&setupFile);
    setupStream << setup;
    setupFile.close();

    QString aliasPath = filePath + "-alias.inscore";
    QFile aliasFile(aliasPath);
    aliasFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream aliasStream(&aliasFile);
    aliasStream << aliases;
    aliasFile.close();


    setup.clear();
    aliases.clear();
    fileName.clear();
}

map<int, INScoreObject *> *INScoreData::getList()
{
    return &objectList;
}

INScoreObject *INScoreData::getObject(const int index)
{
    return objectList[index];
}

QString INScoreData::extractProjectName(QString projectPath)
{
    if(projectPath.isNull()) {
        return "";
    }
    else {
        return projectPath.split("/").last();
    }
}

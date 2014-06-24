#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    entryLineList.clear();
    objectList.clear();
    QObject::connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));
    QObject::connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(readInputs()));
    QObject::connect(ui->newLineButton, SIGNAL(clicked()), this, SLOT(newLine()));
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));

    newIndex = 0;
    newLine();
    newLine();
}

MainInterface::~MainInterface()
{
    delete ui;
}

void MainInterface::newLine()
{
    entryLineList[newIndex] = new INScoreLine(newIndex);
    objectList[newIndex] = new INScoreObject();
    ui->scrollAreaWidgetContents->layout()->addWidget(entryLineList[newIndex]);
    QObject::connect(entryLineList[newIndex], SIGNAL(removeLine(const int)), this, SLOT(removeObjects(const int)));
    ++newIndex;
}

void MainInterface::readInputs()
{
    projectName = QFileDialog::getSaveFileName(this,QString("Save"),QString("../../../.."));
    if(!projectName.isNull()) {  // <- if no name, nothing is done
        dom = new XmlData();
        map<int, INScoreObject*>::iterator it = objectList.begin();
        while(it != objectList.end()) {
            if((entryLineList[it->first]->objectName().isEmpty())) { // <- if the object has no name, we remove it
                int toDelete = it->first;
                ++it;
                removeObjects(toDelete);
            }
            else {
                it->second->setName((entryLineList[it->first]->objectName()).toStdString());
                it->second->setPath((entryLineList[it->first]->objectPath()).toStdString());
                it->second->setToCreate(entryLineList[it->first]->isToCreate());
                it->second->setType((entryLineList[it->first]->selectedType()).toStdString());
                if(!entryLineList[it->first]->getCreationValue().isEmpty()) {
                    it->second->setCreationValue(entryLineList[it->first]->getCreationValue().toStdString());
                }

                int j(0);
                while(j < entryLineList[it->first]->nbCheckBoxes()) {
                    string paramName = (entryLineList[it->first]->selectedParameter(j)).toStdString();
                    bool paramValue =  entryLineList[it->first]->parameterValue(paramName);
                    it->second->setParameter(paramName , paramValue);
                    ++j;
                }
                ++it;
            }
        }
        writeXML();
        generateINScoreSetup();
        delete dom;
    }
}

void MainInterface::loadFile()
{
    dom = new XmlData();
    projectName = QFileDialog::getOpenFileName(this,QString("Load"),QString("../../.."));
    if (!projectName.isNull()) {
        dom->readFile(projectName);
        dom->xmlToInscoreObject();
    }

    int i(0);
    while(i<dom->nbInscoreObject()) {
        newLine();
        entryLineList[newIndex-1]->setLine(dom->getObject(i));
        ++i;
    }
    delete dom;
}

void MainInterface::removeObjects(const int num)
{
    objectList.erase(num);
    entryLineList.erase(num);
}

void MainInterface::quitApp()
{
    int quit = QMessageBox::question(this, "Close Application", "Do you really want to close the application ?", QMessageBox::Yes | QMessageBox::No);
    if(quit == QMessageBox::Yes) {
        qApp->quit();
    }
}

QString MainInterface::extractProjectName()
{
    if(projectName.isNull()) {
        return "";
    }
    else {
        return projectName.split("/").last();
    }
}


void MainInterface::writeXML()
{
     /* generates the dom object */
     dom->generateXML(&objectList);

     /* writes it in a file (name asked to user) */
     if (!projectName.isNull()) {
         QString fileName = projectName + "-iscore.xml";
         dom->writeFile(fileName);
     }
}


void MainInterface::writeINScore()
{
    /* write the 2 inscore files */
   QString setupPath = projectName + "-setup.inscore";
   QFile setupFile(setupPath);
   setupFile.open(QIODevice::WriteOnly | QIODevice::Text);

   QTextStream setupStream(&setupFile);
   setupStream << inscoreSetup;

   setupFile.close();

   QString aliasPath = projectName + "-alias.inscore";
   QFile aliasFile(aliasPath);
   aliasFile.open(QIODevice::WriteOnly | QIODevice::Text);

   QTextStream aliasStream(&aliasFile);
   aliasStream << inscoreAliases;
   aliasFile.close();
}

void MainInterface::generateINScoreSetup()
{
    inscoreSetup.clear();
    inscoreAliases.clear();

    inscoreAliases = "! This file contains aliases instruction for INScore \n";
    inscoreAliases = inscoreAliases + "! It has to be conform with the i-score OSC tree (.xml) \n";
    inscoreAliases = inscoreAliases + "! in a normal use, you DON'T have to MODIFY this file \n";
    inscoreAliases = inscoreAliases + "! ************************************************************** \n \n";

    inscoreSetup = "! This file contains the init value for the INScore object \n";
    inscoreSetup = inscoreSetup + "! You can adjust it at your will \n";
    inscoreSetup = inscoreSetup + "!  ************************************************************** \n \n";

    if(objectList.empty()) {
        QMessageBox::critical(NULL,"Error","Nothing to generate !");
        return;
    }
    map<int, INScoreObject*>::iterator pairIt= objectList.begin();

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

    string signal = "signal";
    while(pairIt!=objectList.end())
    {
        INScoreObject * it(pairIt->second);
        string OSCaddress = string("\"/") + (it)->getScene() + "/" + (it)->getName() + "/"; // OSC address for an object
        string inscoreAddress = (it)->getPath();
        string method = "";
        string reAllocateSignal = string("/ITL/") + (it)->getScene() + string(" watch+ endPaint ("); // watch for new value for a signal to draw it in the graph
        /* Creating the setup */
        if((it)->getToCreate()) {
            /* Rules for graph element : building signals */
            if((it)->getType().compare("graph") == 0) {
                string signalPath = string("/ITL/") + (it)->getScene() + "/signal" ;
                string setSignal = signalPath + "/" + (it)->getCreationValue() + " set ";
                int k = 0;
                while(k< (it)->getSignalSize())
                {
                    QString inscoreSignalAdress = QString((signalPath + "/" + (it)->getSignal(k) + (it)->getName()).c_str());
                    inscoreSetup = inscoreSetup + inscoreSignalAdress + QString((" size " + (it)->getBufferSize(k) + "; \n").c_str());
                    inscoreSetup = inscoreSetup + inscoreSignalAdress + QString((" default " + (it)->getSignalValue(k) + "; \n").c_str());
                    inscoreAliases = inscoreAliases + inscoreSignalAdress + QString((" alias \"/" + (it)->getScene() + "/" + (it)->getName() + "/signal/" + (it)->getSignal(k) + "\"; \n").c_str());
                    setSignal = setSignal + (it)->getSignal(k) + (it)->getName() +  " ";
                    ++k;
                }
                // set signal : set y t h s b a
                inscoreSetup = inscoreSetup + QString((setSignal + "; \n").c_str());
                // add a watch command to display new value
                inscoreSetup = inscoreSetup + QString((reAllocateSignal + inscoreAddress + " set " + (it)->getType() + " " + (it)->getCreationValue() + "); \n").c_str());
            }
            /* Setup for all new element */
            string inscoreNewAddress = inscoreAddress + " set " + (it)->getType() + " " + (it)->getCreationValue();
            inscoreSetup = inscoreSetup + QString((inscoreNewAddress + ";" + "\n").c_str());
            inscoreSetup = inscoreSetup + QString((inscoreAddress + " show 0;" + "\n").c_str());
        }

        int i = 0;
        /* creating aliases for all parameter */
        while(i<dom->getNbParameters()) {
            string currentParam = dom->getParameter(i)->getParameterName();
            if((it)->isParameterChecked(currentParam)) {
                string OSCparamAddress = OSCaddress + currentParam + "/"; // loop to add each parameter
                int j = 0;
                while(j<dom->getParameter(i)->getNbVariable()) {
                    inscoreAddress = (it)->getPath();
                    method = dom->getParameter(i)->getVariable(j).getVariableName();
                    if(signal.compare(dom->getParameter(i)->getParameterName()) != 0) {
                        string OSCfinalAddress = OSCparamAddress + dom->getParameter(i)->getVariable(j).getVariableName() + "\""; // loop to add each variable
                        inscoreAliases = inscoreAliases + QString((inscoreAddress + " alias " + OSCfinalAddress + " " + method + ";" + "\n").c_str()); // and write
                    }
                    j++;
                }
            }
            i++;
        }
        inscoreSetup = inscoreSetup + QString("\n");
        inscoreAliases = inscoreAliases +  QString("\n");
        ++pairIt;
    }
    QString aliasFile = extractProjectName();
    inscoreSetup = inscoreSetup + "/ITL load \"" + aliasFile + "-alias.inscore\"; \n";
    writeINScore();
}

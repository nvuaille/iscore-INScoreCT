#include "../headers/maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    entryLineList.clear();
    dataContainer = new INScoreData();

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
    dataContainer->addObject(newIndex);
    ui->scrollAreaWidgetContents->layout()->addWidget(entryLineList[newIndex]);
    QObject::connect(entryLineList[newIndex], SIGNAL(removeLine(const int)), this, SLOT(removeObjects(const int)));
    QObject::connect(entryLineList[newIndex], SIGNAL(advancedOptions(const int)), this, SLOT(advancedOptionsWindow(const int)));
    ++newIndex;
}

void MainInterface::readInputs()
{
    projectName = QFileDialog::getSaveFileName(this,QString("Save"),QString("../../../.."),tr("*.conf"));
    if(!projectName.isNull()) {  // <- if no save name, nothing is done
        dom = new XmlData();

        map<int, INScoreObject*> *objectList = dataContainer->getList();
        map<int, INScoreObject*>::iterator it = objectList->begin();
        while(it != objectList->end()) {
            if((entryLineList[it->first]->objectName().isEmpty())) { // <- if the object has no name, we remove it
                int toDelete = it->first;
                ++it;
                removeObjects(toDelete);
            }
            else {
                it->second->setName((entryLineList[it->first]->objectName()).toStdString()); // Name
                it->second->setPath((entryLineList[it->first]->objectPath()).toStdString()); // path
                it->second->setToCreate(entryLineList[it->first]->isToCreate()); // to create
                it->second->setType((entryLineList[it->first]->selectedType()).toStdString()); // type
                if(!entryLineList[it->first]->getCreationValue().isEmpty()) { // init value if not empty
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
        writeXML(projectName);
        dataContainer->writeFiles(projectName);
        delete dom;
    }
}

void MainInterface::loadFile()
{
    dom = new XmlData();
    projectName = QFileDialog::getOpenFileName(this,QString("Load"),QString("../../.."), QString("*.conf"));
    if (!projectName.isNull()) {
        clearAll();
        dom->readFile(projectName);
        dom->xmlToInscoreObject();
        int i(0);
        while(i<dom->nbInscoreObject()) {
            newLine();
            entryLineList[newIndex-1]->setLine(dom->getObject(i));
            dataContainer->addObject(i,*(dom->getObject(i)));
            ++i;
        }
    }
    delete dom;
}

void MainInterface::removeObjects(const int num)
{
    if(entryLineList.find(num) != entryLineList.end()) {
        dataContainer->removeObject(num);
        entryLineList[num]->close();
        entryLineList.erase(num);
    }
}

void MainInterface::clearAll()
{
    int erase = QMessageBox::question(this, "Clear all", "Do you really want to clear all the current configuration ?", QMessageBox::Yes | QMessageBox::No);
    if(erase == QMessageBox::Yes) {
        for(int i= 0; i< newIndex; ++i) {
            removeObjects(i);
        }
        newIndex = 0;
    }
}

void MainInterface::quitApp()
{
    int quit = QMessageBox::question(this, "Close Application", "Do you really want to close the application ?", QMessageBox::Yes | QMessageBox::No);
    if(quit == QMessageBox::Yes) {
        qApp->quit();
    }
}

void MainInterface::advancedOptionsWindow(const int num)
{
    optWindow = new AdvancedOptions();
    optWindow->displayInitValues(dataContainer->getObject(num));
    optWindow->exec();

    optWindow->close();
    delete optWindow;
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

void MainInterface::writeXML(QString projectPath)
{
     /* generate the dom object */
     dom->generateOSCTree(dataContainer->getList());

     /* write it in a file (name asked to user) */
     QString fileName = projectPath + "-iscore.xml";
     dom->writeFile(fileName);

     dom->generateSaveFile(dataContainer->getList());
     fileName = projectPath + ".conf";
     dom->writeFile(fileName);
}

void MainInterface::on_clearButton_clicked()
{
    clearAll();
}

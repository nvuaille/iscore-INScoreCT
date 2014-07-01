#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include "inscoreline.h"
#include "inscoredata.h"
#include "xmldata.h"
#include "advancedoptions.h"

namespace Ui {
    class MainInterface;
}

class MainInterface : public QWidget
{
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = 0);
    ~MainInterface();

    /* ********************************************************
     * calls the XML_Dom::generateXML and write the file
     * calls generateINScoreSetup()
     *
     * called by "read()"
     * ********************************************************/
    void writeXML();

    /* ********************************************************
     * writes the inscore files :
     * alias file and setup file
     * ********************************************************/
    void writeINScore();

    /* ********************************************************
     * generates the INScore instructions for the setup
     * i.e. to create new object and all aliases
     * ********************************************************/
    void generateINScoreSetup();


public slots:

    /* ********************************************************
     *  Creates a new inscoreLine
     *
     * A line as this content :
     *  name - path - checkBox with parameters - object type
     *
     * ********************************************************/
    void newLine();

    /* ********************************************************
     * Read the datas from GUI
     * ********************************************************/
    void readInputs();

    void loadFile();

    void removeObjects(const int num);

    void quitApp();

    void advancedOptionsWindow(const int num);

private:
    Ui::MainInterface *ui;

    AdvancedOptions *optWindow;

    /* list of all inscoreObject to include in the setup */

    INScoreData *dataContainer;
    map<int, INScoreLine*> entryLineList;

    XmlData *dom; // = new XmlData();

    /* contain text to write in inscore setup file */
    QString inscoreSetup;

    /* contain text to write in inscore aliases file */
    QString inscoreAliases;

    /* name used for the created files, filled in by user */
    QString projectName;

    QString extractProjectName();

    int newIndex;

};

#endif // MAININTERFACE_H

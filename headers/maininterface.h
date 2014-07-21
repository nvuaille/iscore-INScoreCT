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
     * call the XML_Dom::generateXML and write the file
     * call generateINScoreSetup()
     * ********************************************************/
    void writeXML(QString projectPath);

public slots:

    /* ********************************************************
     *  Create a new inscoreLine
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

    /* ********************************************************
     * load an existing work
     * ********************************************************/
    void loadFile();

    /* ********************************************************
     * Remove the object from the list of INScore ojects
     * ********************************************************/
    void removeObjects(const int num);

    /* ********************************************************
     * Clear all the entries
     * ********************************************************/
    void clearAll();

    /* ********************************************************
     * Close the app
     * ********************************************************/
    void quitApp();

    /* ********************************************************
     * open the Window containing the advanced options
     * of the current object
     * ********************************************************/
    void advancedOptionsWindow(const int num);

private slots:
    void on_clearButton_clicked();

private:
    Ui::MainInterface *ui;

    /* Pop up window for advanced options */
    AdvancedOptions *optWindow;

    /* list of all inscoreObject to include in the setup */
    INScoreData *dataContainer;

    /* list of INScoreLine */
    map<int, INScoreLine*> entryLineList;

    /* contain data for the xml files */
    XmlData *dom;

    /* name used for the created files, filled in by user */
    QString projectName;

    QString extractProjectName();

    int newIndex;

};

#endif // MAININTERFACE_H

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
     * called by "readInputs()"
     * ********************************************************/
    void writeXML(QString projectPath);

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

    void clearAll();

    void quitApp();

    void advancedOptionsWindow(const int num);

private slots:
    void on_clearButton_clicked();

private:
    Ui::MainInterface *ui;

    AdvancedOptions *optWindow;

    /* list of all inscoreObject to include in the setup */

    INScoreData *dataContainer;
    map<int, INScoreLine*> entryLineList;

    XmlData *dom; // = new XmlData();

    /* name used for the created files, filled in by user */
    QString projectName;

    QString extractProjectName();

    int newIndex;

};

#endif // MAININTERFACE_H

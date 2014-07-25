#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "inscoreline.h"
#include "maininterface.h"

namespace Ui {
class MainWindow;
}

/* ********************************************************
 * This class generates the GUI, reads the user's inputs
 * and transform the informations into xml tree for i-score
 * and OSC instruction for INScore
 * ********************************************************/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void closeEvent(QCloseEvent *event);
private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

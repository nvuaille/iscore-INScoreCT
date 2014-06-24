#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);

    this->setCentralWidget(new MainInterface);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
    int quit = QMessageBox::question(this, "Close Application", "Do you really want to close the application ?", QMessageBox::Yes | QMessageBox::No);
    if(quit == QMessageBox::Yes) {
         event->accept();
    }
    else {
         event->ignore();
    }
 }

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QToolBar>
#include <QMenuBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mUi(new Ui::MainWindow)
    , mToDoList(new ToDoListWidget(this))
{
    mUi->setupUi(this);
    SetupMenu();
    SetupToolBar();
    statusBar()->showMessage("Ready");
    setCentralWidget(mToDoList);
}

MainWindow::~MainWindow()
{
    delete mUi;
}

void MainWindow::SetupMenu(void)
{
    menuBar()->addAction("&File");
    menuBar()->addAction("&Edit");
    menuBar()->addAction("&Help");
}

void MainWindow::SetupToolBar(void)
{
    QToolBar *toolBar = addToolBar(tr("File"));
    QAction *newAct = new QAction(QIcon::fromTheme("document-new", QIcon(":/icons/new.png")),
                                  tr("&New"),
                                  this);
    toolBar->addAction(newAct);

    QAction *openAct = new QAction(QIcon::fromTheme("document-new", QIcon(":/icons/open.png")),
                                  tr("&Open"),
                                  this);
    toolBar->addAction(openAct);

    QAction *saveAct = new QAction(QIcon::fromTheme("document-new", QIcon(":/icons/save.png")),
                                  tr("&Save"),
                                  this);
    toolBar->addAction(saveAct);
}

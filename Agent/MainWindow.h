#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ToDoList/ToDoListWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SetupMenu(void);
    void SetupToolBar(void);

    Ui::MainWindow *mUi;
    ToDoListWidget *mToDoList;
};
#endif // MAINWINDOW_H

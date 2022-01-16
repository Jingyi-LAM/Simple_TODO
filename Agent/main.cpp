#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("Arial");
    a.setFont(f);

    MainWindow w;
    w.show();
    return a.exec();
}

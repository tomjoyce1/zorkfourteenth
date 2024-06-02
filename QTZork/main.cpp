//VERY IMPORTANT

//WIN32_EXECUTABLE TRUE to WIN32_EXECUTABLE FALSE - required to make cin and cout play nicely with QT. By the time the project's finished, you'll want to be able to turn this back on again
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

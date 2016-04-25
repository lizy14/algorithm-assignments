#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int x=233;
    x+=1;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

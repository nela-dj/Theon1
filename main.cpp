#include "predmetqt.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PredmetQt w;
    w.show();

    return a.exec();
}

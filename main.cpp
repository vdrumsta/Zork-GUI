#include "mainwindow.h"
#include <QApplication>
#include <vector>

using namespace std;
#include "ZorkUL.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}

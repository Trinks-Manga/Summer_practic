#include "mainwindow.h"
#include "field.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(new Field());
    w.show();

    return a.exec();
}

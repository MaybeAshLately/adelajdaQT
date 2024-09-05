#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color: #FFFF86;");
    w.setWindowTitle("Adelajda");
    w.show();
    return a.exec();
}

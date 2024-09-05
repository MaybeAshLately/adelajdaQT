#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <iostream>
#include <QStandardPaths>
#include <filesystem>
#include <QString>
#include <QDir>

/*
 * 1. pobieranie z pliku nazw list
 * 2. ustawianie ich na liście
 * 3. uruchamianie nowej aktywności dodawania nowej listy
 * 4. uruchamianie nowej aktywności widoku listy po kliknięciu w element listy
 * 5. Reładowanie nazw list jeśli lista została usunięta lub dodana
 *
 *
 *
 * */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setImage();
    getListNamesFromFileNamesInDirectory();
    setNamesOnWidgetList();
}

void MainWindow::setImage()
{
   QGraphicsScene *scene = new QGraphicsScene(this);
   QPixmap pixmap(":/new/prefix1/app_icon.jpeg");
   pixmap=pixmap.scaled(249,249,Qt::KeepAspectRatio);
   QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
   scene->addItem(item);
   scene->setSceneRect(pixmap.rect());
   ui->image->setScene(scene);
}

void MainWindow::setNamesOnWidgetList()
{
    for(size_t i=0;i<listNames.size();++i)
    {
        ui->listWidget->addItem(listNames.at(i));
    }
    ui->listWidget->addItem("hiszpanski");
    ui->listWidget->addItem("polski");
    ui->listWidget->addItem("angielski");
    ui->listWidget->addItem("jidysz");
}

void MainWindow::getListNamesFromFileNamesInDirectory()
{

    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data";

    QDir dir(dataPath);

    if(dir.exists()==false)
    {
        dir.mkpath(dataPath);
    }


    for(const auto & i: std::filesystem::directory_iterator(dataPath.toStdString()))
    {
        QString fileBuffer=QString::fromStdString(i.path().filename().string());
        listNames.push_back(fileBuffer);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_new_list_clicked()
{

}


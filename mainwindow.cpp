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
#include "addnewlist.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);
    setImage();
    getListNamesFromFileNamesInDirectory();
    setNamesOnWidgetList();
    ui->add_new_list->setStyleSheet("background-color: #00BA0C;");
    ui->listWidget->setStyleSheet("QListWidget::item { border-bottom: 1px solid gray; padding: 5px; }");
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
    setListWidgetSize();
}


void MainWindow::setListWidgetSize()
{
    int width = ui->add_new_list->width();
    int height = ui->listWidget->sizeHintForRow(0)*ui->listWidget->count()+ui->listWidget->count()*(1+5+5+1);
    ui->listWidget->setFixedSize(width, height);
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


void MainWindow::on_add_new_list_clicked()
{
    AddNewList* w;
    w= new AddNewList(this);
    w->setStyleSheet("background-color: #FFFF86;");
    w->setWindowTitle("Add list");
    w->setFixedSize(800,600);

    connect(w, &AddNewList::finished, this, &MainWindow::addNewListFinished);
    this->hide();
    w->show();
}


void MainWindow::addNewListFinished()
{
    this->show();
    if(dataTransfer.newListAdded==true)
    {
        listNames.push_back(dataTransfer.newListName);
        ui->listWidget->clear();
        setNamesOnWidgetList();
        dataTransfer.newListAdded=false;
        dataTransfer.newListName="";
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

}


MainWindow::~MainWindow()
{
    delete ui;
}

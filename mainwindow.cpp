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
#include "listoptions.h"


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
    ui->listWidget->clear();

    for(size_t i=0;i<listNames.size();++i)
    {
        ui->listWidget->addItem(listNames.at(i));
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->listWidget->setStyleSheet("QListWidget::item { border-bottom: 1px solid gray; padding: 5px; }");
}


void MainWindow::getListNamesFromFileNamesInDirectory()
{
    listNames.clear();
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
        getListNamesFromFileNamesInDirectory();
        setNamesOnWidgetList();
        dataTransfer.newListAdded=false;
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString itemName= item->text();
    dataTransfer.currentListName=itemName;

    ListOptions* w;
    w= new ListOptions(this);
    w->setStyleSheet("background-color: #FFFF86;");
    w->setWindowTitle(itemName);
    w->setFixedSize(800,600);

    connect(w, &ListOptions::finished, this, &MainWindow::listOptionsFinished);
    this->hide();
    w->show();
}


void MainWindow::listOptionsFinished()
{
    this->show();
    if(dataTransfer.listDeleted==true)
    {
        getListNamesFromFileNamesInDirectory();
        setNamesOnWidgetList();
        dataTransfer.listDeleted=false;
        dataTransfer.currentListName="";
        dataTransfer.currentListLanguageOneName="";
        dataTransfer.currentListLanguageTwoName="";
    }
    if(dataTransfer.listNameModified==true)
    {
        getListNamesFromFileNamesInDirectory();
        setNamesOnWidgetList();
        dataTransfer.listNameModified=false;
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

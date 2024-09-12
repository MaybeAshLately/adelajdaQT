#include "listoptions.h"
#include "ui_listoptions.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QStandardPaths>
#include <fstream>

ListOptions::ListOptions(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListOptions)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);

    ui->displayButton->setStyleSheet("background-color: #911785;");
    ui->learningModeAButton->setStyleSheet("background-color: #3569F9;");
    ui->learningModeBButton->setStyleSheet("background-color: #3569F9;");
    ui->addNewWordButton->setStyleSheet("background-color: #00BA0C;");
    ui->settingsButton->setStyleSheet("background-color: #C0C0C0;");
    ui->goBackButton->setStyleSheet("background-color: #C0C0C0;");

    ui->nameLabel->setText(dataTransfer.currentListName);

    setImage();
    goBackToMain=false;

    storeLanguageNames();
}


void ListOptions::setImage()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(":/new/prefix1/app_icon.jpeg");
    pixmap=pixmap.scaled(249,249,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
    scene->setSceneRect(pixmap.rect());
    ui->image->setScene(scene);
}


void ListOptions::on_goBackButton_clicked()
{
    goBackToMain=true;
    this->close();
}


void ListOptions::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit finished(0);

    if(goBackToMain==true)
    {
        QDialog::closeEvent(event);
        emit finished(0);
    }
    else
    {
        QApplication::quit();
    }
}


void ListOptions::storeLanguageNames()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";

    std::string directory=dataPath.toStdString()+dataTransfer.currentListName.toStdString();

    std::string lineBuffer;

    std::ifstream file(directory);
    if(file)
    {
        std::getline(file,lineBuffer);
    }
    file.close();

    QString line=QString::fromStdString(lineBuffer);

    if(line!="")
    {
        QStringList splitBuffer=line.split(";");
        dataTransfer.currentListLanguageOneName=splitBuffer[0];
        dataTransfer.currentListLanguageTwoName=splitBuffer[1];
    }
}


void ListOptions::on_learningModeBButton_clicked()
{

}


void ListOptions::on_displayButton_clicked()
{

}


void ListOptions::on_addNewWordButton_clicked()
{

}


void ListOptions::on_learningModeAButton_clicked()
{

}


void ListOptions::on_settingsButton_clicked()
{

}


ListOptions::~ListOptions()
{
    delete ui;
}

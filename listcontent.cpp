#include "listcontent.h"
#include "ui_listcontent.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QStandardPaths>
#include <fstream>

ListContent::ListContent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListContent)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);
    ui->addNewWordButton->setStyleSheet("background-color: #00BA0C;");
    ui->goBackButton->setStyleSheet("background-color: #C0C0C0;");

    ui->listName->setText(dataTransfer.currentListName);
    ui->languageOneName->setText(dataTransfer.currentListLanguageOneName);
    ui->languageTwoName->setText(dataTransfer.currentListLanguageTwoName);

    setImage();
    goBack=false;

    getDataFromFile();
    setNamesOnWidgetList();

}


void ListContent::setImage()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(":/new/prefix1/app_icon.jpeg");
    pixmap=pixmap.scaled(249,249,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
    scene->setSceneRect(pixmap.rect());
    ui->image->setScene(scene);
}


void ListContent::getDataFromFile()
{
    fileContent.clear();
    languageOneWords.clear();
    languageTwoWords.clear();
    comments.clear();
    colors.clear();

    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";

    std::string directory=dataPath.toStdString()+dataTransfer.currentListName.toStdString();

    std::string lineBuffer;

    std::ifstream file(directory);
    if(file)
    {
        while(std::getline(file,lineBuffer)) fileContent.push_back(QString::fromStdString(lineBuffer));
    }
    file.close();

    for(size_t i=1;i<fileContent.size();++i)
    {
        if(fileContent.at(i)!="")
        {
            QStringList splitBuffer=fileContent.at(i).split(";");
            languageOneWords.push_back(splitBuffer[0]);
            languageTwoWords.push_back(splitBuffer[1]);
            comments.push_back(splitBuffer[2]);
            colors.push_back(splitBuffer[3]);
        }
    }
}


void ListContent::setNamesOnWidgetList()
{
    ui->listWidget->clear();

    for(size_t i=0;i<languageOneWords.size();++i)
    {
        ui->listWidget->addItem(languageOneWords.at(i)+" - "+languageTwoWords.at(i));
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    setListWidgetSize();
    ui->listWidget->setStyleSheet("QListWidget::item { border-bottom: 1px solid gray; padding: 5px; }");
}


void ListContent::setListWidgetSize()
{
    int height = ui->listWidget->sizeHintForRow(0)*ui->listWidget->count()+ui->listWidget->count()*(1+5+5+1+1);
    ui->listWidget->setFixedHeight(height);
}



void ListContent::closeEvent(QCloseEvent *event)
{
    if(goBack==true)
    {
        emit finished(0);
    }
    else
    {
        QApplication::quit();
    }
}


void ListContent::on_goBackButton_clicked()
{
    goBack=true;
    this->close();
}


void ListContent::on_addNewWordButton_clicked()
{
    AddNewWord* w;
    w= new AddNewWord(this);
    w->setStyleSheet("background-color: #FFFF86;");
    w->setWindowTitle("Add new word");
    w->setFixedSize(800,600);

    connect(w, &AddNewWord::finished, this, &ListContent::addingWordFinished);
    this->hide();
    w->show();
}


void ListContent::addingWordFinished()
{
    if(dataTransfer.newWordAdded==true)
    {
        getDataFromFile();
        setNamesOnWidgetList();

        dataTransfer.newWordAdded=false;
        //dataTransfer.newWordToDisplay="";
    }
    this->show();
}


ListContent::~ListContent()
{
    delete ui;
}

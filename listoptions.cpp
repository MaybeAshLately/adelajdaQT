#include "listoptions.h"
#include "ui_listoptions.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QStandardPaths>
#include <QFile>

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
    if(goBackToMain==true)
    {
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
    QString directory=dataPath+dataTransfer.currentListName;

    QString line;
    QFile file(directory);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        line=file.readLine();
    }
    file.close();

    if(line!="")
    {
        QStringList splitBuffer=line.split(";");
        dataTransfer.currentListLanguageOneName=splitBuffer[0];
        dataTransfer.currentListLanguageTwoName=splitBuffer[1];
    }
}


void ListOptions::on_learningModeAButton_clicked()
{
    LearningModeA* w;
    w= new LearningModeA(this);
    w->setWindowTitle("Learning mode A");
    w->setFixedSize(800,600);

    connect(w, &LearningModeA::finished, this, &ListOptions::learningFinished);
    this->hide();
    w->show();
}


void ListOptions::learningFinished()
{
    this->show();
}


void ListOptions::on_learningModeBButton_clicked()
{
    LearningModeB* w;
    w= new LearningModeB(this);
    w->setWindowTitle("Learning mode B");
    w->setFixedSize(800,600);

    connect(w, &LearningModeB::finished, this, &ListOptions::learningFinished);
    this->hide();
    w->show();
}


void ListOptions::on_displayButton_clicked()
{
    ListContent* w;
    w= new ListContent(this);
    w->setStyleSheet("background-color: #FFFF86;");
    w->setWindowTitle(dataTransfer.currentListName);
    w->setFixedSize(800,600);

    connect(w, &ListContent::finished, this, &ListOptions::listFinished);
    this->hide();
    w->show();
}

void ListOptions::listFinished()
{
    this->show();
}


void ListOptions::on_addNewWordButton_clicked()
{
    AddNewWord* w;
    w= new AddNewWord(this);
    w->setStyleSheet("background-color: #FFFF86;");
    w->setWindowTitle("Add new word");
    w->setFixedSize(800,600);

    connect(w, &AddNewWord::finished, this, &ListOptions::addingWordFinished);
    this->hide();
    w->show();
}


void ListOptions::addingWordFinished()
{
    this->show();
}


void ListOptions::on_settingsButton_clicked()
{
    ListSettings* w;
    w= new ListSettings(this);
    w->setStyleSheet("background-color: #FFFF86;");
    w->setWindowTitle("Settings");
    w->setFixedSize(800,600);

    connect(w, &ListSettings::finished, this, &ListOptions::settingsFinished);
    this->hide();
    w->show();
}


void ListOptions::settingsFinished()
{
    ui->nameLabel->setText(dataTransfer.currentListName);
    if(!dataTransfer.listDeleted) this->show();
    else
    {
        goBackToMain=true;
        this->close();
    }

}


ListOptions::~ListOptions()
{
    delete ui;
}

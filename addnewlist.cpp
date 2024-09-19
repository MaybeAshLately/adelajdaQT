#include "addnewlist.h"
#include "ui_addnewlist.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QDir>
#include <QStandardPaths>
#include <algorithm>
#include <cctype>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>



AddNewList::AddNewList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddNewList)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);
    setImage();
    goBackToMain=false;

    ui->cancelButton->setStyleSheet("background-color: #FF0000;");
    ui->addNewListButton->setStyleSheet("background-color: #00BA0C;");

}


void AddNewList::setImage()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(":/new/prefix1/app_icon.jpeg");
    pixmap=pixmap.scaled(249,249,Qt::KeepAspectRatio);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
    scene->setSceneRect(pixmap.rect());
    ui->image->setScene(scene);
}


void AddNewList::on_cancelButton_clicked()
{
    goBackToMain=true;
    this->close();
}


void AddNewList::closeEvent(QCloseEvent *event)
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


void AddNewList::on_addNewListButton_clicked()
{
    listName=ui->enter_list_name_edit_text->toPlainText();
    languageOneName=ui->enter_language_1_name_edit_text->toPlainText();
    languageTwoName=ui->enter_language_2_name_edit_text->toPlainText();

    if(checkIfNamesCorrect()==true) addList();
    else displayInfo();
}


bool AddNewList::checkIfNamesCorrect() const
{
    if((listName=="")||(languageOneName=="")||(languageTwoName=="")) return false;
    if((checkIfNameCorrect(listName)==false)||(checkIfNameCorrect(languageOneName)==false)||(checkIfNameCorrect(languageTwoName)==false)) return false;
    if(checkIfNameUnique()==false) return false;

    return true;
}


bool AddNewList::checkIfNameCorrect(const QString string) const
{
    for(int i=0;i<string.size();++i)
    {
        QChar buf=string.at(i);
        if((buf.isLetterOrNumber()==false)&&(buf!='_')&&(buf!=' ')) return false;
    }
    return true;
}


bool AddNewList::checkIfNameUnique() const
{
    QVector<QString> buffer;
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data";

    for(const auto & i: std::filesystem::directory_iterator(dataPath.toStdString()))
    {
        QString fileBuffer=QString::fromStdString(i.path().filename().string());
        buffer.push_back(fileBuffer);
    }

    if(std::find(buffer.begin(),buffer.end(),listName)==buffer.end()) return true;
    return false;
}


void AddNewList::addList()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";
    QString directory=dataPath+listName;

    QFile file(directory);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream out(&file);
        out<<languageOneName+";"+languageTwoName<<"\n";
    }
    file.close();

    dataTransfer.newListAdded=true;

    goBackToMain=true;
    this->close();
}


void AddNewList::displayInfo()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Wrong names");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("All names can consist only of alphanumeric signs, spaces and underscores. They cannot be empty. Name of list must be unique.");
    layout->addWidget(label);

    QPushButton *okButton = new QPushButton("Ok");
    okButton->setStyleSheet("background-color: #C0C0C0;");
    layout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, [&dialog](){dialog.close();} );

    dialog.exec();
}


AddNewList::~AddNewList()
{
    delete ui;
}


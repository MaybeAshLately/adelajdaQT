#include "singleword.h"
#include "ui_singleword.h"
#include <iostream>

SingleWord::SingleWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SingleWord)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);

    ui->listName->setText(dataTransfer.currentListName);
    ui->language1Name->setText(dataTransfer.currentListLanguageOneName);
    ui->language2Name->setText(dataTransfer.currentListLanguageTwoName);

    ui->goBackButton->setStyleSheet("background-color: #C0C0C0;");
    ui->editWordButton->setStyleSheet("background-color: #3569F9;");
    ui->removeWordButton->setStyleSheet("background-color: #FF0000;");
    setData();

    goBack=false;
}


void SingleWord::setData()
{
    ui->language1Word->setText(dataTransfer.currentWordLanguageOne);
    ui->language1Word->setFixedWidth(ui->language1Word->width());
    ui->language1Word->setAlignment(Qt::AlignCenter);

    ui->language2Word->setText(dataTransfer.currentWordLanguageTwo);
    ui->language2Word->setFixedWidth(ui->language2Word->width());
    ui->language2Word->setAlignment(Qt::AlignCenter);


    ui->commentText->setText(dataTransfer.currentComment);
    ui->commentText->setAlignment(Qt::AlignCenter);

    QString color=dataTransfer.currentColor;

    if(color=="red") this->setStyleSheet("background-color: #FF0000;");
    else if(color=="green") this->setStyleSheet("background-color: #00BA0C;");
    else if(color=="yellow") this->setStyleSheet("background-color: #FFF700;");
    else if(color=="orange") this->setStyleSheet("background-color: #FF9A00;");
    else if(color=="blue") this->setStyleSheet("background-color: #3569F9;");
    else if(color=="white") this->setStyleSheet("background-color: #FFFFFF;");
    else if(color=="purple") this->setStyleSheet("background-color: #911785;");
    else if(color=="pink") this->setStyleSheet("background-color: #FF99CC;");
    else if(color=="gray") this->setStyleSheet("background-color: #C0C0C0;");
    else this->setStyleSheet("background-color: #FFFF86;");

   // this->update();

}


void SingleWord::closeEvent(QCloseEvent *event)
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


void SingleWord::on_goBackButton_clicked()
{
    goBack=true;
    this->close();
}


void SingleWord::on_editWordButton_clicked()
{

}


void SingleWord::on_removeWordButton_clicked()
{

}


SingleWord::~SingleWord()
{
    delete ui;
}

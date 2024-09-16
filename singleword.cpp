#include "singleword.h"
#include "ui_singleword.h"
#include <iostream>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <fstream>
#include <QTextEdit>
#include <QRadioButton>

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
    editWord();
}


void SingleWord::on_removeWordButton_clicked()
{
    askIfDeleteWord();
}


void SingleWord::askIfDeleteWord()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Delete word");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("This action cannont be undone. Are you sure you want to delete this word?");
    layout->addWidget(label);

    QPushButton *cancelButton = new QPushButton("Cancel");
    layout->addWidget(cancelButton);
    cancelButton->setStyleSheet("background-color: #00BA0C;");
    connect(cancelButton, &QPushButton::clicked,&dialog, [&dialog](){dialog.close();} );


    QPushButton *yesButton = new QPushButton("Yes");
    layout->addWidget(yesButton);
    yesButton->setStyleSheet("background-color: #FF0000;");
    connect(yesButton, &QPushButton::clicked,&dialog, [this, &dialog](){
        deleteWord();
        dialog.close();
    } );

    dialog.exec();
}


void SingleWord::deleteWord()
{
    std::vector<QString> fileContent;
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";
    std::string directory=dataPath.toStdString()+dataTransfer.currentListName.toStdString();

    std::string lineBuffer;

    std::ifstream file(directory);
    if(file)
    {
        while(std::getline(file,lineBuffer)) fileContent.push_back(QString::fromStdString(lineBuffer));
    }
    file.close();

    fileContent.erase(fileContent.begin()+dataTransfer.currentItemNumber+1);

    std::ofstream newFile(directory);
    if(newFile)
    {
        for(size_t i=0;i<fileContent.size();++i)
        {
            newFile<<fileContent.at(i).toStdString()<<std::endl;
        }
    }

   dataTransfer.wordDeleted=true;
   dataTransfer.currentWordLanguageOne="";
   dataTransfer.currentWordLanguageTwo="";
   dataTransfer.currentComment="";
   dataTransfer.currentColor="";
   dataTransfer.currentItemNumber=0;

   goBack=true;
   this->close();

}


void SingleWord::editWord()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Edit word");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QGridLayout *gridLayout = new QGridLayout();


    QLabel *labelLan1 = new QLabel(dataTransfer.currentListLanguageOneName);
    QTextEdit *languageOneWord = new QTextEdit(dataTransfer.currentWordLanguageOne);
    languageOneWord->setMaximumHeight(30);
    gridLayout->addWidget(labelLan1, 0, 0, 1, 5);
    gridLayout->addWidget(languageOneWord, 1, 0, 1, 5);


    QLabel *labelLan2 = new QLabel(dataTransfer.currentListLanguageTwoName);
    QTextEdit *languageTwoWord = new QTextEdit(dataTransfer.currentWordLanguageTwo);
    languageTwoWord->setMaximumHeight(30);
    gridLayout->addWidget(labelLan2, 0, 5, 1, 5);
    gridLayout->addWidget(languageTwoWord, 1, 5, 1, 5);


    QLabel *labelCom = new QLabel("Comment");
    QTextEdit *commentWord = new QTextEdit(dataTransfer.currentComment);
    commentWord->setMaximumHeight(30);
    gridLayout->addWidget(labelCom, 2, 0, 1, 10);
    gridLayout->addWidget(commentWord, 3, 0, 1, 10);


    QRadioButton *beige = new QRadioButton("beige");
    gridLayout->addWidget(beige,4,0,1,1);
    QRadioButton *red = new QRadioButton("red");
    gridLayout->addWidget(red,4,1,1,1);
    QRadioButton *green = new QRadioButton("green");
    gridLayout->addWidget(green,4,2,1,1);
    QRadioButton *yellow = new QRadioButton("yellow");
    gridLayout->addWidget(yellow,4,3,1,1);
    QRadioButton *orange = new QRadioButton("orange");
    gridLayout->addWidget(orange,4,4,1,1);
    QRadioButton *blue = new QRadioButton("blue");
    gridLayout->addWidget(blue,4,5,1,1);
    QRadioButton *white = new QRadioButton("white");
    gridLayout->addWidget(white,4,6,1,1);
    QRadioButton *purple = new QRadioButton("purple");
    gridLayout->addWidget(purple,4,7,1,1);
    QRadioButton *pink = new QRadioButton("pink");
    gridLayout->addWidget(pink,4,8,1,1);
    QRadioButton *gray = new QRadioButton("gray");
    gridLayout->addWidget(gray,4,9,1,1);


    QPushButton *cancelButton = new QPushButton("Cancel");
    gridLayout->addWidget(cancelButton, 5, 0, 1, 5);
    cancelButton->setStyleSheet("background-color: #FF0000;");
    connect(cancelButton, &QPushButton::clicked,&dialog, [&dialog](){dialog.close();} );


    QPushButton *yesButton = new QPushButton("Save");
    gridLayout->addWidget(yesButton, 5, 5, 1, 5);
    yesButton->setStyleSheet("background-color: #00BA0C;");
    connect(yesButton, &QPushButton::clicked,&dialog, [this,&dialog, languageOneWord, languageTwoWord, commentWord, beige, red, green, yellow, orange, blue, white, purple, pink, gray](){
        QString newWordOne,newWordTwo, newCom, newCol;
        newWordOne=languageOneWord->toPlainText();
        newWordTwo=languageTwoWord->toPlainText();
        newCom=commentWord->toPlainText();


        if(beige->isChecked()) newCol="beige";
        else if(red->isChecked()) newCol="red";
        else if(green->isChecked()) newCol="green";
        else if(yellow->isChecked()) newCol="yellow";
        else if(orange->isChecked()) newCol="orange";
        else if(blue->isChecked()) newCol="blue";
        else if(white->isChecked()) newCol="white";
        else if(purple->isChecked()) newCol="purple";
        else if(pink->isChecked()) newCol="pink";
        else if(gray->isChecked()) newCol="gray";
        else newCol=dataTransfer.currentColor;

        saveChanges(newWordOne,newWordTwo, newCom, newCol);
        dialog.close();
    } );


    layout->addLayout(gridLayout);

    dialog.exec();
}


void SingleWord::saveChanges(QString newWordOne,QString newWordTwo,QString newCom,QString newCol)
{
    if((newWordOne==dataTransfer.currentWordLanguageOne)&&(newWordTwo==dataTransfer.currentWordLanguageTwo)&&(newCom==dataTransfer.currentComment)&&(newCol==dataTransfer.currentColor)) return;
    if((newWordOne=="")||(newWordTwo=="")||(newWordOne.contains(";"))||(newWordTwo.contains(";"))||(newCom.contains(";")))
    {
        displayInfo();
        return;
    }

    std::vector<QString> fileContent;
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";
    std::string directory=dataPath.toStdString()+dataTransfer.currentListName.toStdString();

    std::string lineBuffer;

    std::ifstream file(directory);
    if(file)
    {
        while(std::getline(file,lineBuffer)) fileContent.push_back(QString::fromStdString(lineBuffer));
    }
    file.close();

    fileContent.at(dataTransfer.currentItemNumber+1)=newWordOne+";"+newWordTwo+";"+newCom+";"+newCol;

    std::ofstream newFile(directory);
    if(newFile)
    {
        for(size_t i=0;i<fileContent.size();++i)
        {
            newFile<<fileContent.at(i).toStdString()<<std::endl;
        }
    }

    dataTransfer.wordEdited=true;
    dataTransfer.currentWordLanguageOne=newWordOne;
    dataTransfer.currentWordLanguageTwo=newWordTwo;
    dataTransfer.currentComment=newCom;
    dataTransfer.currentColor=newCol;
    setData();

}


void SingleWord::displayInfo()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Wrong names");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Word fields cannot be empty. None of field can contain ; sign.");
    layout->addWidget(label);

    QPushButton *okButton = new QPushButton("Ok");
    layout->addWidget(okButton);
    okButton->setStyleSheet("background-color: #C0C0C0;");
    connect(okButton, &QPushButton::clicked,this, [&dialog](){dialog.close();} );

    dialog.exec();
}


SingleWord::~SingleWord()
{
    delete ui;
}

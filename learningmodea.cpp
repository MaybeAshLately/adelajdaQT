#include "learningmodea.h"
#include "ui_learningmodea.h"
#include <QGridLayout>
#include <QRadioButton>
#include <QTimer>
#include <algorithm>
#include <random>
#include <QStandardPaths>
#include <fstream>

LearningModeA::LearningModeA(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningModeA)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);
    goBack=false;
    currentNumber=0;
    setData();
    mode=Mode::LAN_ONE;
    displayStartInfo();

    setUpRandom();
    setWord();
}


void LearningModeA::setData()
{
    ui->listName->setText(dataTransfer.currentListName);

    ui->revealButton->setStyleSheet("background-color: #911785;");
    ui->previousWordButton->setStyleSheet("background-color: #3569F9;");
    ui->nextWordButton->setStyleSheet("background-color: #00BA0C;");
    ui->endButton->setStyleSheet("background-color: #C0C0C0;");
    ui->resetButton->setStyleSheet("background-color: #FF99CC;");

    ui->languageAWord->setText("");
    ui->languageBWord->setText("");
    ui->commentText->setText("");
    ui->commentText->setAlignment(Qt::AlignCenter);
}


void LearningModeA::displayStartInfo()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Learning mode A start");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QGridLayout *gridLayout = new QGridLayout();

    QLabel *labelName = new QLabel(dataTransfer.currentListName);
    labelName->setStyleSheet("font-weight:bold");
    gridLayout->addWidget(labelName, 0, 1, 1, 3);

    QLabel *labelLan1 = new QLabel(dataTransfer.currentListLanguageOneName);
    labelLan1->setStyleSheet("font-weight:bold");
    gridLayout->addWidget(labelLan1, 1, 0, 1, 2);
    QLabel *labelLan2 = new QLabel(dataTransfer.currentListLanguageTwoName);
    labelLan2->setStyleSheet("font-weight:bold");
    gridLayout->addWidget(labelLan2, 1, 2, 1, 1);


    QLabel *labelInfo1 = new QLabel("In the learning mode A app will display word in selected language. After you click on it, app will reveal its translation and comment (if available).");
    gridLayout->addWidget(labelInfo1, 2, 0, 1, 3);

    QLabel *labelInfo2 = new QLabel("Display word from:");
    gridLayout->addWidget(labelInfo2, 3, 1, 1, 3);



    QRadioButton *lan1 = new QRadioButton(dataTransfer.currentListLanguageOneName);
    gridLayout->addWidget(lan1,4,0,1,1);
    QRadioButton *lan2 = new QRadioButton(dataTransfer.currentListLanguageTwoName);
    gridLayout->addWidget(lan2,4,1,1,1);
    QRadioButton *both = new QRadioButton("both");
    gridLayout->addWidget(both,4,2,1,1);


    QPushButton *yesButton = new QPushButton("Ok");
    gridLayout->addWidget(yesButton, 5, 0, 1, 3);
    yesButton->setStyleSheet("background-color: #00BA0C;");
    connect(yesButton, &QPushButton::clicked,&dialog, [this, &dialog, lan1, lan2, both](){
        if(lan2->isChecked()) this->mode=Mode::LAN_TWO;
        else if(both->isChecked()) this->mode=Mode::BOTH;
        else this->mode=Mode::LAN_ONE;
        dialog.close();
    } );


    layout->addLayout(gridLayout);

    dialog.exec();
}


void LearningModeA::setUpRandom()
{
    getDataFromFile();
    for(int i=0;i<languageOneWords.size();i++) numbers.push_back(i);

    generateRandom();
}


void LearningModeA::getDataFromFile()
{
    languageOneWords.clear();
    languageTwoWords.clear();
    comments.clear();
    colors.clear();


    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";
    std::string directory=dataPath.toStdString()+dataTransfer.currentListName.toStdString();


    QVector<QString> listContentBuffer;
    std::ifstream file(directory);
    if(file)
    {
        std::string lineBuffer;
        while(std::getline(file,lineBuffer)) listContentBuffer.push_back(QString::fromStdString(lineBuffer));
    }
    file.close();


    if(listContentBuffer.size()>1)
    {
        for(int i=1;i<listContentBuffer.size();i++)
        {
            QStringList lineBuffer=listContentBuffer.at(i).split(";");

            languageOneWords.push_back(lineBuffer[0]);
            languageTwoWords.push_back(lineBuffer[1]);
            comments.push_back(lineBuffer[2]);
            colors.push_back(lineBuffer[3]);
        }
    }
}


void LearningModeA::generateRandom()
{
    auto rd=std::random_device{};
    auto rng=std::default_random_engine{rd()};
    std::shuffle(numbers.begin(), numbers.end(), rng);
}


void LearningModeA::setWord()
{
    if(mode==Mode::LAN_ONE)
    {
        ui->languageAWord->setText(languageOneWords.at(numbers.at(currentNumber)));
        currentWordIsLanguageOne=true;
        ui->languageAName->setText(dataTransfer.currentListLanguageOneName);
    }
    else
    {
        ui->languageAWord->setText(languageTwoWords.at(numbers.at(currentNumber)));
        currentWordIsLanguageOne=false;
        ui->languageAName->setText(dataTransfer.currentListLanguageTwoName);
    }

    ui->languageBWord->setText("");
    ui->languageBName->setText("");
    ui->commentText->setText("");
    setColor(colors.at(numbers.at(currentNumber)));
}


void LearningModeA::setNewWord()
{
    if(currentWordIsLanguageOne==true)
    {
        ui->languageAWord->setText(languageOneWords.at(numbers.at(currentNumber)));
        ui->languageAName->setText(dataTransfer.currentListLanguageOneName);
    }
    else
    {
        ui->languageAWord->setText(languageTwoWords.at(numbers.at(currentNumber)));
        ui->languageAName->setText(dataTransfer.currentListLanguageTwoName);
    }

    ui->languageBWord->setText("");
    ui->languageBName->setText("");
    ui->commentText->setText("");
    setColor(colors.at(numbers.at(currentNumber)));
}


void LearningModeA::setColor(QString color)
{
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


void LearningModeA::on_revealButton_clicked()
{
    if(currentWordIsLanguageOne==true)
    {
        ui->languageBWord->setText(languageTwoWords.at(numbers.at(currentNumber)));
        ui->languageBName->setText(dataTransfer.currentListLanguageTwoName);
    }
    else
    {
        ui->languageBWord->setText(languageOneWords.at(numbers.at(currentNumber)));
        ui->languageBName->setText(dataTransfer.currentListLanguageOneName);
    }
    ui->commentText->setText(comments.at(numbers.at(currentNumber)));
}


void LearningModeA::on_previousWordButton_clicked()
{
    if(currentNumber==0) return;
    currentNumber=currentNumber-1;
    if(mode==Mode::BOTH) currentWordIsLanguageOne=!currentWordIsLanguageOne;
    setNewWord();
}


void LearningModeA::on_nextWordButton_clicked()
{
    if(currentNumber+1<languageOneWords.size())
    {
        currentNumber++;
        if(mode==Mode::BOTH) currentWordIsLanguageOne=!currentWordIsLanguageOne;
        setNewWord();
    }
    else endOfData();
}


void LearningModeA::endOfData()
{
    QDialog dialog(this);

    dialog.setWindowTitle("End of data");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QGridLayout *gridLayout = new QGridLayout();

    QLabel *labelName = new QLabel("Congratulations! You have reach an end of words in this list.");
    gridLayout->addWidget(labelName, 0, 1);

    QPushButton *finishButton = new QPushButton("Finish");
    gridLayout->addWidget(finishButton, 1, 0);
    finishButton->setStyleSheet("background-color: #C0C0C0;");
    connect(finishButton, &QPushButton::clicked,&dialog, [this, &dialog](){
        goBack=true;
        this->close();
        dialog.close();
    } );

    QPushButton *startOverButton = new QPushButton("Start over");
    gridLayout->addWidget(startOverButton, 1, 1);
    startOverButton->setStyleSheet("background-color: #00BA0C;");
    connect(startOverButton, &QPushButton::clicked,&dialog, [this, &dialog](){
        this->startOver();
        dialog.close();
    } );


    layout->addLayout(gridLayout);

    dialog.exec();
}


void LearningModeA::on_endButton_clicked()
{
    goBack=true;
    this->close();
}


void LearningModeA::closeEvent(QCloseEvent *event)
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


void LearningModeA::on_resetButton_clicked()
{
    startOver();
}


void LearningModeA::startOver()
{
    generateRandom();
    currentNumber=0;
    setWord();
}


LearningModeA::~LearningModeA()
{
    delete ui;
}

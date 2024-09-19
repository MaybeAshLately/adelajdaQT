#include "learningmodeb.h"
#include "ui_learningmodeb.h"
#include <QStandardPaths>
#include <random>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFile>

LearningModeB::LearningModeB(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningModeB)
    , dataTransfer(DataTransfer::getInstance())
{
    ui->setupUi(this);
    goBack=false;
    setData();

    displayStartInfo();
    setUpRandom();
    setWord();
}


void LearningModeB::setData()
{
    mode=Mode::LAN_ONE;
    misspellMode=MisspellMode::SKIP;

    hiddenWord=true;
    repeatLastWord=false;
    repeatedWord=false;
    currentNumber=0;

    ui->listName->setText(dataTransfer.currentListName);

    ui->previousWordButton->setStyleSheet("background-color: #3569F9;");
    ui->nextWordButton->setStyleSheet("background-color: #00BA0C;");
    ui->endButton->setStyleSheet("background-color: #C0C0C0;");
    ui->resetButton->setStyleSheet("background-color: #FF99CC;");

    ui->languageAWord->setText("");
    ui->languageBWord->setText("");
    ui->commentText->setText("");
    ui->commentText->setAlignment(Qt::AlignCenter);

    ui->nextWordButton->setText("Reveal");
}


void LearningModeB::displayStartInfo()
{
    QDialog dialog(this);

    dialog.setWindowTitle("Learning mode B start");
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


    QLabel *labelInfo1 = new QLabel("In the learning mode B, the app will display a word. The user can fill in its translation and then check if it is correct.");
    gridLayout->addWidget(labelInfo1, 2, 0, 1, 3);
    QLabel *labelInfo2 = new QLabel("You can choose whether you want to fill in translations in the first, second, or both languages. You can also choose whether to skip, repeat immediately, or repeat later any misspelled word.");
    gridLayout->addWidget(labelInfo2, 3, 0, 1, 3);

    QLabel *labelInfo3 = new QLabel("Display word from:");
    gridLayout->addWidget(labelInfo3, 4, 1, 1, 3);

    QRadioButton *lan1 = new QRadioButton(dataTransfer.currentListLanguageOneName);
    gridLayout->addWidget(lan1,5,0,1,1);
    QRadioButton *lan2 = new QRadioButton(dataTransfer.currentListLanguageTwoName);
    gridLayout->addWidget(lan2,5,1,1,1);
    QRadioButton *both = new QRadioButton("both");
    gridLayout->addWidget(both,5,2,1,1);

    QButtonGroup *group1 = new QButtonGroup(this);
    group1->addButton(lan1);
    group1->addButton(lan2);
    group1->addButton(both);


    QLabel *labelInfo4 = new QLabel("After misspelling word:");
    gridLayout->addWidget(labelInfo4, 6, 1, 1, 3);

    QRadioButton *skip = new QRadioButton("Skip it");
    gridLayout->addWidget(skip,7,0,1,1);
    QRadioButton *repeat = new QRadioButton("Repeat");
    gridLayout->addWidget(repeat,7,1,1,1);
    QRadioButton *repeatLater = new QRadioButton("Repeat later");
    gridLayout->addWidget(repeatLater,7,2,1,1);

    QButtonGroup *group2 = new QButtonGroup(this);
    group2->addButton(skip);
    group2->addButton(repeat);
    group2->addButton(repeatLater);



    QPushButton *yesButton = new QPushButton("Ok");
    gridLayout->addWidget(yesButton, 8, 0, 1, 3);
    yesButton->setStyleSheet("background-color: #00BA0C;");
    connect(yesButton, &QPushButton::clicked,&dialog, [this, &dialog, lan1, lan2, both, skip, repeat, repeatLater](){
        if(lan2->isChecked()) this->mode=Mode::LAN_TWO;
        else if(both->isChecked()) this->mode=Mode::BOTH;
        else this->mode=Mode::LAN_ONE;

        if(repeat->isChecked()) this->misspellMode=MisspellMode::REPEAT;
        else if(repeatLater->isChecked()) this->misspellMode=MisspellMode::REPEAT_LATER;
        else this->misspellMode=MisspellMode::SKIP;
        dialog.close();
    } );


    layout->addLayout(gridLayout);

    dialog.exec();
}


void LearningModeB::closeEvent(QCloseEvent *event)
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


void LearningModeB::getDataFromFile()
{
    languageOneWords.clear();
    languageTwoWords.clear();
    comments.clear();
    colors.clear();

    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/data/";
    QString directory=dataPath+dataTransfer.currentListName;

    QVector<QString> listContentBuffer;

    QFile file(directory);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while(!file.atEnd()) listContentBuffer.push_back(file.readLine());
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


void LearningModeB::setUpRandom()
{
    getDataFromFile();
    for(int i=0;i<languageOneWords.size();i++) numbers.push_back(i);

    generateRandom();
}


void LearningModeB::generateRandom()
{
    auto rd=std::random_device{};
    auto rng=std::default_random_engine{rd()};
    std::shuffle(numbers.begin(), numbers.end(), rng);
}


void LearningModeB::nextWord()
{
    if(repeatLastWord==true)
    {
        setNewWord(currentNumber);
        repeatLastWord=false;
    }
    else
    {
        if(currentNumber+1<languageOneWords.size())
        {
            currentNumber++;
            if(mode==Mode::BOTH) currentWordIsLanguageOne=!currentWordIsLanguageOne;
            setNewWord(currentNumber);
        }
        else endOfData();
    }
}


void LearningModeB::setWord()
{
    if(mode==Mode::LAN_ONE)
    {
        ui->languageAWord->setText(languageOneWords.at(numbers.at(currentNumber)));
        currentWordIsLanguageOne=true;
        ui->languageAName->setText(dataTransfer.currentListLanguageOneName);
        ui->languageBName->setText(dataTransfer.currentListLanguageTwoName);
    }
    else
    {
        ui->languageAWord->setText(languageTwoWords.at(numbers.at(currentNumber)));
        currentWordIsLanguageOne=false;
        ui->languageAName->setText(dataTransfer.currentListLanguageTwoName);
        ui->languageBName->setText(dataTransfer.currentListLanguageOneName);
    }

    ui->resultText->setText("");
    ui->languageBWord->setText("");
    ui->commentText->setText("");
    setColor(colors.at(numbers.at(currentNumber)));
}


void LearningModeB::setNewWord(int num)
{
    if(currentWordIsLanguageOne==true)
    {
        ui->languageAWord->setText(languageOneWords.at(numbers.at(num)));
        ui->languageAName->setText(dataTransfer.currentListLanguageOneName);
        ui->languageBName->setText(dataTransfer.currentListLanguageTwoName);
    }
    else
    {
        ui->languageAWord->setText(languageTwoWords.at(numbers.at(num)));
        ui->languageAName->setText(dataTransfer.currentListLanguageTwoName);
        ui->languageBName->setText(dataTransfer.currentListLanguageOneName);
    }

    ui->textEdit->setText("");
    ui->languageBWord->setText("");
    ui->commentText->setText("");
    ui->resultText->setText("");
    setColor(colors.at(numbers.at(num)));
}


void LearningModeB::setColor(QString color)
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


void LearningModeB::startOver()
{
    repeatAfter.clear();
    repeatedWord=false;
    generateRandom();
    currentNumber=0;
    setWord();
}


void LearningModeB::endOfData()
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


void LearningModeB::reveal(int num)
{
    if(currentWordIsLanguageOne==true)
    {
        ui->languageBWord->setText(languageTwoWords.at(numbers.at(num)));
    }
    else
    {
        ui->languageBWord->setText(languageOneWords.at(numbers.at(num)));
    }
    ui->commentText->setText(comments.at(numbers.at(num)));
}



void LearningModeB::nextWordIsRepeated()
{
    if(repeatLastWord==true)
    {
        setNewWord(currentNumber);
        repeatLastWord=false;
    }
    else
    {
        setNewWord(repeatAfter.value(currentNumber));
        repeatedWord=true;
    }
}


void LearningModeB::checkIfCorrectAndHandle(int num)
{
    QString enteredAnswer=ui->textEdit->toPlainText();
    if((enteredAnswer.size()>1)&&(enteredAnswer.at(enteredAnswer.size()-1)==' ')) enteredAnswer=enteredAnswer.removeLast();

    if((currentWordIsLanguageOne==true)&&((QString::compare(enteredAnswer, languageTwoWords.at(numbers.at(num)),Qt::CaseInsensitive))==0))
    {
        ui->resultText->setText("Correct!");
        handleCorrectRepeatedWord();
    }
    else if((currentWordIsLanguageOne==false)&&((QString::compare(enteredAnswer, languageOneWords.at(numbers.at(num)),Qt::CaseInsensitive))==0))
    {
        ui->resultText->setText("Correct!");
        handleCorrectRepeatedWord();
    }
    else
    {
        if(repeatedWord==false) incorrect();
        else handleNotCorrectRepeatedWord();
    }

}


void LearningModeB::handleCorrectRepeatedWord() {
    if (repeatedWord == true)
    {
        repeatAfter.remove(currentNumber);
        repeatedWord=false;
    }
}


void LearningModeB::handleNotCorrectRepeatedWord()
{
    ui->resultText->setText("Error!");

    auto rd=std::random_device{};
    auto rng=std::default_random_engine{rd()};
    std::uniform_int_distribution<int> dist(0,numbers.size()-1);

    int showAfter=dist(rng)+currentNumber;
    int buffer=repeatAfter.value(currentNumber);
    repeatAfter.remove(currentNumber);
    repeatAfter.insert(showAfter,buffer);
    repeatedWord=false;
}


void LearningModeB::incorrect()
{
    ui->resultText->setText("Error!");

    if(misspellMode==MisspellMode::SKIP) return;

    if(misspellMode==MisspellMode::REPEAT) {repeatLastWord=true;}
    if(misspellMode==MisspellMode::REPEAT_LATER) {
        addToQueue();
    }
}


void LearningModeB::addToQueue()
{
    auto rd=std::random_device{};
    auto rng=std::default_random_engine{rd()};
    std::uniform_int_distribution<int> dist(0,numbers.size());

    int showAfter=dist(rng)+currentNumber;
    repeatAfter.insert(showAfter,currentNumber);

}


void LearningModeB::on_previousWordButton_clicked()
{
    if(currentNumber==0) return;
    currentNumber=currentNumber-1;
    if(mode==Mode::BOTH) currentWordIsLanguageOne=!currentWordIsLanguageOne;
    setNewWord(currentNumber);
}


void LearningModeB::on_nextWordButton_clicked()
{
    if(hiddenWord==true)
    {
        if(repeatedWord==false)
        {
            reveal(currentNumber);
            checkIfCorrectAndHandle(currentNumber);
        }
        else
        {
            reveal(repeatAfter.value(currentNumber));
            checkIfCorrectAndHandle(repeatAfter.value(currentNumber));
        }
        ui->nextWordButton->setText("Next word");
        hiddenWord=false;
    }
    else
    {
        if(repeatAfter.contains(currentNumber)==false) nextWord();
        else nextWordIsRepeated();

        ui->nextWordButton->setText("Reveal");
        hiddenWord=true;
    }
}


void LearningModeB::on_endButton_clicked()
{
    goBack=true;
    this->close();
}


void LearningModeB::on_resetButton_clicked()
{
    startOver();
}


LearningModeB::~LearningModeB()
{
    delete ui;
}

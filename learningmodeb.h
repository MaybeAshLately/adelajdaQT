#ifndef LEARNINGMODEB_H
#define LEARNINGMODEB_H

#include <QDialog>
#include "DataTransfer.h"
#include <QVector>
#include <QMap>

namespace Ui {
class LearningModeB;
}

class LearningModeB : public QDialog
{
    Q_OBJECT

public:
    explicit LearningModeB(QWidget *parent = nullptr);
    ~LearningModeB();

private slots:
    void on_previousWordButton_clicked();

    void on_nextWordButton_clicked();

    void on_endButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::LearningModeB *ui;
    DataTransfer& dataTransfer;
    bool goBack;

    QVector<QString> languageOneWords;
    QVector<QString> languageTwoWords;
    QVector<QString> comments;
    QVector<QString> colors;
    QVector<int> numbers;
    int currentNumber;
    bool currentWordIsLanguageOne;

    bool repeatLastWord;
    bool repeatedWord;

    bool hiddenWord;
    QMap<int,int> repeatAfter;

    void setUpRandom();
    void getDataFromFile();
    void generateRandom();



    void setData();
    void displayStartInfo();

    void closeEvent(QCloseEvent *event);

    enum class Mode{
        LAN_ONE,
        LAN_TWO,
        BOTH
    };
    Mode mode;

    enum class MisspellMode{
        SKIP,
        REPEAT,
        REPEAT_LATER
    };
    MisspellMode misspellMode;

    void setNewWord(int num);
    void setWord();
    void setColor(QString color);
    void startOver();
    void endOfData();

    void reveal(int num);
    void nextWord();
    void nextWordIsRepeated();

    void checkIfCorrectAndHandle(int num);
    void handleCorrectRepeatedWord();
    void handleNotCorrectRepeatedWord();
    void incorrect();
    void addToQueue();
};

#endif // LEARNINGMODEB_H

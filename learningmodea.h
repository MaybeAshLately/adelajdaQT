#ifndef LEARNINGMODEA_H
#define LEARNINGMODEA_H

#include <QDialog>
#include "DataTransfer.h"
#include <QVector>

namespace Ui {
class LearningModeA;
}

class LearningModeA : public QDialog
{
    Q_OBJECT

public:
    explicit LearningModeA(QWidget *parent = nullptr);
    ~LearningModeA();

private slots:
    void on_revealButton_clicked();

    void on_previousWordButton_clicked();

    void on_nextWordButton_clicked();

    void on_endButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::LearningModeA *ui;
    DataTransfer& dataTransfer;
    bool goBack;

    QVector<QString> languageOneWords;
    QVector<QString> languageTwoWords;
    QVector<QString> comments;
    QVector<QString> colors;
    QVector<int> numbers;
    int currentNumber;
    bool currentWordIsLanguageOne;

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

    void setNewWord();
    void setWord();
    void setColor(QString color);
    void startOver();
    void endOfData();

};

#endif // LEARNINGMODEA_H

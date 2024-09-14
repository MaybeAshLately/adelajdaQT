#ifndef ADDNEWWORD_H
#define ADDNEWWORD_H

#include <QDialog>
#include "DataTransfer.h"

namespace Ui {
class AddNewWord;
}

class AddNewWord : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewWord(QWidget *parent = nullptr);
    ~AddNewWord();

private slots:
    void on_cancelButton_clicked();

    void on_addWordButton_clicked();

private:
    Ui::AddNewWord *ui;
    DataTransfer& dataTransfer;

    bool goBack;

    QString languageOneWord;
    QString languageTwoWord;
    QString comment;
    QString color;

    void closeEvent(QCloseEvent *event);

    bool checkIfCorrect() const;
    void addWord();
    void displayInfo();

};

#endif // ADDNEWWORD_H

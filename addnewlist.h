#ifndef ADDNEWLIST_H
#define ADDNEWLIST_H

#include <QDialog>
#include <QString>
#include "DataTransfer.h"

namespace Ui {
class AddNewList;
}

class AddNewList : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewList(QWidget *parent = nullptr);
    ~AddNewList();

private slots:
    void on_cancelButton_clicked();

    void on_addNewListButton_clicked();

private:
    Ui::AddNewList *ui;
    DataTransfer& dataTransfer;

    QString listName;
    QString languageOneName;
    QString languageTwoName;

    bool goBackToMain;


    void setImage();
    void closeEvent(QCloseEvent *event);

    bool checkIfNamesCorrect();
    bool checkIfNameCorrect(QString string);
    bool checkIfNameUnique();
    void addList();
    void displayInfo();
};

#endif // ADDNEWLIST_H

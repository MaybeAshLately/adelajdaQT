#ifndef SINGLEWORD_H
#define SINGLEWORD_H

#include <QDialog>
#include "DataTransfer.h"


namespace Ui {
class SingleWord;
}

class SingleWord : public QDialog
{
    Q_OBJECT

public:
    explicit SingleWord(QWidget *parent = nullptr);
    ~SingleWord();

private slots:
    void on_goBackButton_clicked();

    void on_editWordButton_clicked();

    void on_removeWordButton_clicked();

private:
    Ui::SingleWord *ui;
    DataTransfer& dataTransfer;
    bool goBack;

    void closeEvent(QCloseEvent *event);
    void setData();

    void deleteWord();
    void askIfDeleteWord();
    void editWord();
    void saveChanges(QString newWordOne,QString newWordTwo,QString newCom,QString newCol);
    void displayInfo();


};

#endif // SINGLEWORD_H

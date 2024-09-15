#ifndef LISTOPTIONS_H
#define LISTOPTIONS_H

#include <QDialog>
#include "DataTransfer.h"
#include "listsettings.h"
#include "addnewword.h"
#include "listcontent.h"


namespace Ui {
class ListOptions;
}

class ListOptions : public QDialog
{
    Q_OBJECT

public:
    explicit ListOptions(QWidget *parent = nullptr);
    ~ListOptions();

private slots:
    void on_goBackButton_clicked();

    void on_learningModeBButton_clicked();

    void on_displayButton_clicked();

    void on_addNewWordButton_clicked();

    void on_learningModeAButton_clicked();

    void on_settingsButton_clicked();

private:
    Ui::ListOptions *ui;
    DataTransfer& dataTransfer;
    bool goBackToMain;

    void setImage();
    void closeEvent(QCloseEvent *event);

    void storeLanguageNames();
    void settingsFinished();
    void addingWordFinished();
    void listFinished();

};

#endif // LISTOPTIONS_H

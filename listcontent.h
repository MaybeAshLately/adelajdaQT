#ifndef LISTCONTENT_H
#define LISTCONTENT_H

#include <QDialog>
#include "DataTransfer.h"
#include "addnewword.h"

namespace Ui {
class ListContent;
}

class ListContent : public QDialog
{
    Q_OBJECT

public:
    explicit ListContent(QWidget *parent = nullptr);
    ~ListContent();

private slots:
    void on_goBackButton_clicked();

    void on_addNewWordButton_clicked();

private:
    Ui::ListContent *ui;
    DataTransfer& dataTransfer;
    bool goBack;
    std::vector<QString> fileContent;
    std::vector<QString> languageOneWords;
    std::vector<QString> languageTwoWords;
    std::vector<QString> comments;
    std::vector<QString> colors;

    void setImage();
    void closeEvent(QCloseEvent *event);

    void getDataFromFile();
    void setNamesOnWidgetList();
    void setListWidgetSize();
    void addingWordFinished();

};

#endif // LISTCONTENT_H

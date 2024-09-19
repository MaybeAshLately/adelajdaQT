#ifndef LISTCONTENT_H
#define LISTCONTENT_H

#include <QDialog>
#include "DataTransfer.h"
#include "addnewword.h"
#include "singleword.h"
#include <QListWidget>
#include <QVector>

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

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::ListContent *ui;
    DataTransfer& dataTransfer;
    bool goBack;
    QVector<QString> fileContent;
    QVector<QString> languageOneWords;
    QVector<QString> languageTwoWords;
    QVector<QString> comments;
    QVector<QString> colors;

    void setImage();
    void closeEvent(QCloseEvent *event);

    void getDataFromFile();
    void setNamesOnWidgetList();
    void addingWordFinished();
    void singleWordFinished();

};

#endif // LISTCONTENT_H

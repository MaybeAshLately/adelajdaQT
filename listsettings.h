#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QDialog>
#include "DataTransfer.h"

namespace Ui {
class ListSettings;
}

class ListSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ListSettings(QWidget *parent = nullptr);
    ~ListSettings();

private slots:
    void on_goBackButton_clicked();

    void on_editNamesButton_clicked();

    void on_deleteListButton_clicked();

private:
    Ui::ListSettings *ui;
    DataTransfer& dataTransfer;
    bool goBackToOptions;

    QString listName;
    QString languageOneName;
    QString languageTwoName;

    void closeEvent(QCloseEvent *event);

    void displayInfo();
    bool checkIfNamesCorrect() const;
    bool checkIfNameCorrect(const QString string) const;
    bool checkIfNameUnique() const;

    void editList();
    void deleteList();

};

#endif // LISTSETTINGS_H

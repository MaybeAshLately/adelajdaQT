#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <string>
#include <QListWidget>
#include "DataTransfer.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_new_list_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    std::vector<QString> listNames;
    DataTransfer& dataTransfer;


    void setImage();
    void getListNamesFromFileNamesInDirectory();
    void setNamesOnWidgetList();
    void setListWidgetSize();
    void addNewListFinished();


};
#endif // MAINWINDOW_H

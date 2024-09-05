#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <string>
#include <QListWidget>


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

private:
    Ui::MainWindow *ui;
    std::vector<QString> listNames;


    void setImage();
    void getListNamesFromFileNamesInDirectory();
    void setNamesOnWidgetList();
};
#endif // MAINWINDOW_H

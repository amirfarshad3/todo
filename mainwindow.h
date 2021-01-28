#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<vector>
#include"task.h"
#include <QMainWindow>
#include<QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void showoldtask();
    void showtask();
    void showcomptask();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();  //add task

    void on_deletTask_clicked();




    void on_Edit_clicked();

    //void on_pushButton_2_clicked();

    void on_completed_clicked();

    void on_ToDo_clicked();

private:
    Ui::MainWindow *ui;
   std::vector<task>input;
};



#endif // MAINWINDOW_H

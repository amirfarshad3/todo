#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include "QMessageBox"
#include "task.h"
#include <QString>
#include <string.h>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QCheckBox>
#include <fstream>
#include "QInputDialog"
#include <QtGui>
#include <QListWidgetItem>
#include <QToolTip>
#include <QDir>
using namespace std;

//__________________________________________________

void MainWindow::showoldtask()
{

    ifstream file("file.txt", ios::in);
    if (!file)
        return;
    task c;
    string name;
    try
    {
        while (getline(file, name))
        {
            c.set_name(QString::fromStdString(name));
            getline(file, name);
            c.set_priority(stoi(name));
            getline(file, name);
            c.set_favorite(name[0]);
            getline(file, name);
            c.set_complate(stoi(name));
            input.push_back(c);
        }
    }

    catch (...)
    {
    }
}

//_________________________________________________________________________________________

void MainWindow::showtask()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    font.setItalic(15);

    ui->widgetOnTheTop->setGeometry(18, 100, 250, 200);

    ui->widgetOnTheTop->setStyleSheet("QListWidget{ background:LightSkyBlue;}"); //for background Color
    ui->widgetOnTheTop->show();
    ui->widgetOnTheTop->setFont(font);
    QVBoxLayout *layout = new QVBoxLayout();
    ui->widgetOnTheTop->clear();
    int i = 1;

    for (auto it = input.begin(); it < input.end(); it++)
    {
        if(it->get_complate()==false){
        if (it->get_favorite() == '*')
        {


            ui->widgetOnTheTop->addItem(new QListWidgetItem(QIcon(":/icon/resorces/iconfavor.png"), QString::number(i) + "_" + it->get_name()));

            i++;
        }
        else if (it->get_favorite() == ' ')
        {
            ui->widgetOnTheTop->addItem("        " + QString::number(i) + "_" + it->get_name());
            i++;
        }
    }
    }

}

//_____________________________________________________________________________

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),

                                          ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QPixmap bkgnd(":/icon/resorces/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    setWindowIcon(QIcon(":/icon/resorces/icon.png"));

    showoldtask();
    showtask();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//____________________________________________________________________________

void MainWindow::on_pushButton_clicked()
{

    ofstream in("file.txt", ios::app); //open the file
    task tmp;
    QString name;
    // char favor;
    bool fOk; //for cancele
    name = QInputDialog::getText(nullptr, "Name", "Enter Name of Task : ", QLineEdit::Normal, "", &fOk);

    if (!fOk) // Cancel button
    {
        return;
    }
    int pri; //priority of task

    pri = QInputDialog::getInt(nullptr, "Priority", "Enter the Priority : ", QLineEdit::Normal, 1, 5, 1, &fOk);

    if (!fOk) // Cancel button
    {
        return;
    }

    QPushButton *YES = new QPushButton; //button no
    QPushButton *NO = new QPushButton;  //button yes
    QMessageBox *favorite = new QMessageBox;
    favorite->setText("do you like this Task? \n ");
    YES = favorite->addButton("YES", QMessageBox::ActionRole);
    NO = favorite->addButton("No", QMessageBox::ActionRole);
    favorite->exec();

    if (favorite->clickedButton() == YES)
    {

        tmp.set_favorite('*');
    }
    else if (favorite->clickedButton() == NO)
    {

        tmp.set_favorite(' ');
    }

    tmp.set_name(name);

    tmp.set_priority(pri);
    tmp.set_complate(false);
    input.push_back(tmp);
    in << tmp.get_name().toStdString() << endl;
    in << tmp.get_priority() << endl;
    in << tmp.get_favorite() << endl;
    in << tmp.get_complate()<<endl;

    QMessageBox *print = new QMessageBox;
    QString text = "Your Task has been successfully added to the List:\n" + tmp.get_name();

    print->setText(text);
    print->exec();
    ui->TodoLabe->setText("ToDo");
    showtask();
}

//______________________________________________________________________________________________

void MainWindow::on_deletTask_clicked()
{

    QMessageBox *delet = new QMessageBox;
    delet->setIcon(QMessageBox::Icon::Warning);
    QPushButton *YES;
    QPushButton *NO;
    QPushButton *can = new QPushButton();
    YES = new QPushButton();
    NO = new QPushButton();

    delet->setWindowIcon(QIcon(":/icon/resorces/icon.png"));

    if (input.empty() == 0)
    {
        can = delet->addButton("Cancle", QMessageBox::ActionRole);
        YES = delet->addButton("YES", QMessageBox::ActionRole);
        NO = delet->addButton("NO", QMessageBox::ActionRole);

        for (auto i = input.begin(); i < input.end(); i++)
        {

            QString name = i->get_name();

            delet->setText(name + "\n" + "Delete?");
            delet->setWindowTitle("delete");
            delet->exec();
            if (delet->clickedButton() == YES)
            {
                input.erase(i);
                ofstream file("file.txt", ios::out);
                for (auto i = input.begin(); i < input.end(); i++)
                {
                    file << i->get_name().toStdString() << endl;
                    file << i->get_priority() << endl;
                    file << i->get_favorite() << endl;
                }

                showtask();
            }
            else if (delet->clickedButton() == can)
            {
                return;
            }
        }
    }
    else if (input.empty() == 1)
    {

        delet->setText("There is No Task!!!");
        delet->exec();
    }
}

//_______________________________________________________________________________________

void MainWindow::on_Edit_clicked() //for editing task
{

    QMessageBox *edit = new QMessageBox;
    QPushButton *YES = new QPushButton;
    QPushButton *NO = new QPushButton;
    edit->setWindowIcon(QIcon(":/icon/resorces/icon.png")); //for icon edit
    if (input.empty() == 0)
    {

        edit->setIcon(QMessageBox::Icon::Question);
        YES = edit->addButton("YES", QMessageBox::ActionRole);
        NO = edit->addButton("NO", QMessageBox::ActionRole);

        for (auto i = input.begin(); i < input.end(); i++)
        {
            QString name = i->get_name();
            edit->setText(name+"\n\n"+"Do you want to Edit this Task?");

            edit->setWindowTitle("edit");

            edit->exec();
            if (edit->clickedButton() == YES)
            {

                edit->removeButton(YES);
                edit->removeButton(NO);
                name = "Name: " + i->get_name() + "\n" + "Priority: " + QString::number(i->get_priority()) + "\n" + "Favorite: " + i->get_favorite();
                edit->setText(name);
                QPushButton *Name = new QPushButton();
                Name = edit->addButton("Name", QMessageBox::ActionRole);
                QPushButton *pri = new QPushButton();
                pri = edit->addButton("Priority", QMessageBox::ActionRole);
                QPushButton *fav = new QPushButton();
                fav = edit->addButton("Favorite", QMessageBox::ActionRole);
                QPushButton *comp = new QPushButton();
                comp = edit->addButton("Completed", QMessageBox::ActionRole);
                QPushButton *cancle = new QPushButton;
                cancle = edit->addButton("OK", QMessageBox::ActionRole);

                bool fOk;

                while (1)
                {

                    if (edit->clickedButton() == cancle)
                    {
                        return;
                    }
                    else if (edit->clickedButton() == Name)
                    {

                        name = QInputDialog::getText(nullptr, "Name", "Enter Name of Task : ", QLineEdit::Normal, "", &fOk);
                        i->set_name(name);
                        name = "Name: " + i->get_name() + "\n" + "Priority: " + QString::number(i->get_priority()) + "\n" + "Favorite: " + i->get_favorite();
                        edit->setText(name);

                        //for update file
                        ofstream file("file.txt", ios::out);
                        for (auto i = input.begin(); i < input.end(); i++)
                        {
                            file << i->get_name().toStdString() << endl;
                            file << i->get_priority() << endl;
                            file << i->get_favorite() << endl;
                            file << i->get_complate() << endl;
                        }

                        file.close();

                        showtask();
                    }
                    else if (edit->clickedButton() == pri)
                    {
                        int pri;

                        pri = QInputDialog::getInt(nullptr, "Priority", "Enter the Priority : ", QLineEdit::Normal, 1, 5, 1, &fOk);
                        i->set_priority(pri);
                        name = "Name: " + i->get_name() + "\n" + "Priority: " + QString::number(i->get_priority()) + "\n" + "Favorite: " + i->get_favorite();
                        edit->setText(name);
                        ofstream file("file.txt", ios::out);
                        for (auto i = input.begin(); i < input.end(); i++)
                        {
                            file << i->get_name().toStdString() << endl;
                            file << i->get_priority() << endl;
                            file << i->get_favorite() << endl;
                            file << i->get_complate() << endl;
                        }

                        file.close();
                        showtask();
                    }
                    else if (edit->clickedButton() == fav)
                    {
                        QMessageBox *favorite = new QMessageBox;
                        favorite->setText("do you like this Task : ");
                        YES = favorite->addButton("YES", QMessageBox::ActionRole);
                        NO = favorite->addButton("No", QMessageBox::ActionRole);
                        favorite->exec();

                        if (favorite->clickedButton() == YES)
                        {

                            i->set_favorite('*');
                            name = "Name: " + i->get_name() + "\n" + "Priority: " + QString::number(i->get_priority()) + "\n" + "Favorite: " + i->get_favorite();
                            edit->setText(name);
                            ofstream file("file.txt", ios::out);
                            for (auto i = input.begin(); i < input.end(); i++)
                            {
                                file << i->get_name().toStdString() << endl;
                                file << i->get_priority() << endl;
                                file << i->get_favorite() << endl;
                                file << i->get_complate() << endl;
                            }
                            file.close();
                        }

                        else if (favorite->clickedButton() == NO)
                        {

                            i->set_favorite(' ');
                            ofstream file("file.txt", ios::out);
                            for (auto i = input.begin(); i < input.end(); i++)
                            {
                                file << i->get_name().toStdString() << endl;
                                file << i->get_priority() << endl;
                                file << i->get_favorite() << endl;
                                file << i->get_complate() << endl;
                            }
                            file.close();
                        }



                        showtask();
                    }
                    else if (edit->clickedButton() == comp)
                    {
                        QMessageBox *c=new QMessageBox;
                        c->setText("This Task Moved to Compeleted Tasks");
                        i->set_complate(true);
                        c->exec();
                        cout << "Error" << i->get_complate() << endl;

                        ofstream file("file.txt", ios::out);
                        for (auto j = input.begin(); j < input.end(); j++)
                        {
                            file << j->get_name().toStdString() << endl;
                            file << j->get_priority() << endl;
                            file << j->get_favorite() << endl;
                            file << j->get_complate() << endl;
                        }
                        file.close();
                    }
                    edit->exec();
                }
            }
        }
    }
}

void MainWindow::showcomptask()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    font.setItalic(15);



    ui->widgetOnTheTop->setStyleSheet("QListWidget{ background:LightSkyBlue;}"); //for background Color
    ui->widgetOnTheTop->show();
    ui->widgetOnTheTop->setFont(font);
    QVBoxLayout *layout = new QVBoxLayout();
    ui->widgetOnTheTop->clear();

    int i = 1;
    for (auto it = input.begin(); it < input.end(); it++)
    {
        if (it->get_complate())
        {

            if (it->get_favorite() == '*')
            {

                ui->widgetOnTheTop->addItem(new QListWidgetItem(QIcon(":/icon/resorces/iconfavor.png"), QString::number(i) + "_" + it->get_name()));

                i++;
            }
            else if (it->get_favorite() == ' ')
            {
                ui->widgetOnTheTop->addItem("        " + QString::number(i) + "_" + it->get_name());
                i++;
            }
        }
    }
    ui->widgetOnTheTop->setLayout(layout);
}

//*************************************************************

void MainWindow::on_completed_clicked()
{

    ui->TodoLabe->setText("List Complete");


    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    font.setItalic(15);

    ui->widgetOnTheTop->setStyleSheet("QListWidget{ background:LightSkyBlue;}"); //for background Color
    ui->widgetOnTheTop->show();
    ui->widgetOnTheTop->setFont(font);
    QVBoxLayout *layout = new QVBoxLayout();
    ui->widgetOnTheTop->clear();

    int i = 1;
    for (auto it = input.begin(); it < input.end(); it++)
    {
        if (it->get_complate())
        {

            if (it->get_favorite() == '*')
            {

                ui->widgetOnTheTop->addItem(new QListWidgetItem(QIcon(":/icon/resorces/iconfavor.png"), QString::number(i) + "_" + it->get_name()));

                i++;
            }
            else if (it->get_favorite() == ' ')
            {
                ui->widgetOnTheTop->addItem("        " + QString::number(i) + "_" + it->get_name());
                i++;
            }
        }
    }

}

//***********************************************************************

void MainWindow::on_ToDo_clicked()
{

    ui->TodoLabe->setText("ToDo");

    showtask();
}

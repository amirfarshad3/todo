#include "task.h"
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <cstdio>
#include <qstring.h>
#include <vector>
#include <random>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include<qstring.h>


using namespace std;
//---------------------------------------------------------------------------
void task::set_id() //function for set id
{
    default_random_engine eng(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<unsigned int> myrand(1000, 9999);
    id = myrand(eng);
}
//---------------------------------------------------------------------------

/*void task::chname(QString newn)
{
    name = newn;
}*/
//---------------------------------------------------------------------------

void task::chfavor(char newf)
{
    favorite = newf;
}
//---------------------------------------------------------------------------

void task::chpri(int newp)
{
    priority = newp;
}
//---------------------------------------------------------------------------

int task::get_id()
{
    return id;
}
//---------------------------------------------------------------------------

void task::set_id(int i)
{
    id = i;
}
//---------------------------------------------------------------------------

void task::set_complate(bool h)
{

    completed = h;
}
//---------------------------------------------------------------------------

bool task::get_complate()
{
    return completed;
}
//---------------------------------------------------------------------------

void task::set_name(QString n)
{
    name = n;
}
//---------------------------------------------------------------------------

QString task::get_name()
{
    return name;
}
//---------------------------------------------------------------------------

void task::set_favorite(char f)
{
    favorite = f;
}
//---------------------------------------------------------------------------

char task::get_favorite()
{

    return favorite;
}
//---------------------------------------------------------------------------

void task::set_priority(int pri)
{

    priority = pri;
}
//---------------------------------------------------------------------------

int task::get_priority()
{

    return priority;
}
//---------------------------------------------------------------------------

void task::delettask(int idd, vector<task> &t) //function for delet task
{
    auto tmp1 = t.begin();
    auto tmp2 = t.end();
    for (auto i = tmp1; i < tmp2; i++) //loop for find task
    {
        if (i->get_id() == idd)
        {
            cout << ">FOUNDED! " << i->get_name().toStdString() << endl
                 << "Delete(y/n)? :  ";
            string d;
            cin >> d; //choice yes or no (y/n) for deleting task
            if (d == "y")
            {
                cout << ">Task\"" << i->get_name().toStdString() << "\",deleted." << endl;
                t.erase(i);
            }
            else if (d == "n")
            {
                return;
            }
            else
            {
                cout << "task didn't choice for delet";
            }
        }
        else if (i->get_id() != idd)
        {
            cout << "Task Not Found" << endl;
        }
    }
}

//---------------------------------------------------------------------------
void task::complete(int id, std::vector<task> &b) //function for complate task
{
    auto tmp1 = b.begin();
    auto tmp2 = b.end();
    for (auto i = tmp1; i < tmp2; i++)
    {
        if (i->get_id() == id) //for find task
        {
            cout << "Founded! " << i->get_name().toStdString() << endl;
            cout << "Complete(y/n): ";
            string n; //for choice yes or no
            cin >> n;
            if (n == "y")
            {
                i->set_complate(true);
                cout << ">Task\"" << i->get_name().toStdString() << "\",completed" << endl;
            }
            else if (n == "n")
                return;
        }
        else
        {
            cout << "Task Not found" << endl;
        }
    }
}

//---------------------------------------------------------------------------

task &task::edit(int id, std::vector<task> &input) //function for edit task
{
    auto tmp1 = input.begin();
    auto tmp2 = input.end();
    bool a = false;
    for (auto i = tmp1; i < tmp2; i++)
    {
        if (i->get_id() == id) // for find task
        {

            while (a == false)
            {

                string s;
                cout << "edit " << i->id << endl;
                cin >> s;
                char a = s[1];
                bool t = true;

                if (a == 'q') //end of edit
                {
                    cout << "edit " << i->id << endl;
                    cout << "-n " << i->get_name().toStdString() << "  -f " << i->get_favorite() << "  -p " << i->get_priority() << endl;
                    a = true;
                    return *this;
                }

                else if (a == 'n') //for change name
                {
                    QString name;
                   // getline(cin, name);
                   // i->chname(name);
                }

                else if (a == 'f') //for change favorite
                {
                    char favaorite;
                    cin >> favorite;
                    i->chfavor(favorite);
                }
                else if (a == 'p')
                {
                    int pri;
                    cin >> pri;
                    i->set_priority(pri);
                }
            }
            return *this;
        }

        else if (i->get_id() != id)
        {
            cout << "task not Found" << endl;
        }
    }
}
//---------------------------------------------------------------------------

bool compare(task &p1, task &p2) //function for sorting tasks
{
    if (p1.get_priority() == p2.get_priority())
    {
        return p1.get_favorite() > p2.get_favorite();
    }
    return p1.get_priority() < p2.get_priority();
}
//---------------------------------------------------------------------------

void task::list_to_do(vector<task> input) //function for show tasks
{
    cout << endl
         << left << setw(40) << "Task" << setw(6) << " P" << setw(4) << "F"
         << "ID" << endl;
    cout << "________________________________________________________" << endl;
    sort(input.begin(), input.end(), compare);
    for (auto i = input.begin(); i < input.end(); i++)
    {
        if (i->get_complate() == false) //show all tasks exept complete
        {
            cout << "-" << setw(40) << i->get_name().toStdString() << setw(5) << i->get_priority() << setw(5) << i->get_favorite() << i->get_id() << endl;
        }
    }
}
//---------------------------------------------------------------------------

void task::list_complate(vector<task> input) //for showing complete tasks
{
    cout << endl
         << left << setw(40) << "Task" << setw(6) << " P" << setw(4) << "F"
         << "ID" << endl;
    cout << "________________________________________________________" << endl;
    sort(input.begin(), input.end(), compare);
    for (auto i = input.begin(); i < input.end(); i++)
    {
        if (i->get_complate()) //show complate task
        {
            cout << "-" << setw(40) << i->get_name().toStdString() << setw(5) << i->get_priority() << setw(5) << i->get_favorite() << i->get_id() << endl;
        }
    }
}

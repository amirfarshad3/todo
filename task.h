#ifndef TASK_H
#define TASK_H
#include<iostream>
#include<qstring.h>
#include <vector>

class task
{
public:
    void set_id();
   // void chname(std::string); //for change name of task
    void chfavor(char);       //for change favorite of task
    void chpri(int);          //for change priority
    void set_id(int);         //for set id
    void set_complate(bool);
    bool get_complate();                      //set random id task
    int get_id();                             //get task id
    void set_name(QString);               //set task name
    QString get_name();                   //get task name
    void set_favorite(char);                  //set favorite task(y/n)
    char get_favorite();                      //get favorite task (y/n)
    void set_priority(int);                   //set priority(1 2 3 4 5)
    int get_priority();                       //get priority
    void delettask(int, std::vector<task> &); //for deleting task
    void complete(int, std::vector<task> &);  //for transfer task to complete tasks
    task &edit(int, std::vector<task> &);     //for edit task with id number
    void list_to_do(std::vector<task>);       //for show list of tasks
    void list_complate(std::vector<task>) ;    //for show list of complate task

        private : int id; //random id task
    QString name;     //name task
    char favorite;        //favorite task (y/n)
    int priority;         //priority task( 1 2 3 4 5 )
    bool completed = false;
};

#endif // TASK_H

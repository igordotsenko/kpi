#ifndef UNTITLED_MANAGER_H
#define UNTITLED_MANAGER_H


#include "Employee.h"
#include <string>
#include <vector>

using namespace std;

class Manager : public Employee  {
private:
    string branch_name;
    vector<Employee*>* subordinates;

public:
    Manager(const string &first_name, const string &last_name, Date *birth_date, const string &name, double salary,
            bool isOpen, Date *enroll_date, const string &branch_name);

    Manager(Manager& manager);
    Manager();

    virtual ~Manager();

    void add_suboridnate(Employee* employee);
    virtual void show();
    virtual void display();
    void display(int min_number_of_subordinates);

    const vector<Employee*> &get_subordinates() const;
};


#endif //UNTITLED_MANAGER_H

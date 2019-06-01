
#ifndef UNTITLED_EMPLOYEE_H
#define UNTITLED_EMPLOYEE_H


#include "Person.h"
#include "Position.h"

class Employee : public Person, public Position {
private:
    Date* enroll_date;

public:
    Employee(const string &first_name, const string &last_name, Date *birth_date, const string &name, double salary,
             bool isOpen, Date *enroll_date);

    Employee();
    Employee(Employee& employee);

    virtual ~Employee();

    virtual void show();
    virtual void display();
    void display(Date& min_enroll_date);
};


#endif //UNTITLED_EMPLOYEE_H


#include "Employee.h"

Employee::Employee(
        const string &first_name,
        const string &last_name,
        Date *birth_date,
        const string &name,
        double salary,
        bool isOpen,
        Date *enroll_date)
        :
        Person(first_name, last_name, birth_date),
        Position(name, salary, isOpen),
        enroll_date(enroll_date) {

    cout << "Employee is created. Size is: " << sizeof(Employee) << endl;
}

Employee::Employee() {
    enroll_date = new Date(2000, 1, 1);
    cout << "Employee default constructor" << endl;
}

Employee::Employee(Employee &employee) : Person(employee), Position(employee) {
    enroll_date = new Date(*employee.enroll_date);
    cout << "Employee copy constructor" << endl;
}

Employee::~Employee() {
    delete enroll_date;
    cout << "Employee is deleted" << endl;
}

void Employee::show() {
    cout << "This is Employee: ";
    display();
}

void Employee::display() {
    Person::display();
    Position::display();
    cout <<"Enroll date: " << *enroll_date << endl;
}

void Employee::display(Date &min_enroll_date) {
    cout << "Display employee if enroll data > " << min_enroll_date << ": " << endl;
    if (enroll_date->get_year() >= min_enroll_date.get_year()
        && enroll_date->get_month() >= min_enroll_date.get_month()
        && enroll_date->get_date() >= min_enroll_date.get_date()) {
        display();
    }
}

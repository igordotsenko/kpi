#include "Manager.h"

Manager::Manager(
        const string &first_name,
        const string &last_name,
        Date *birth_date,
        const string &name,
        double salary,
        bool isOpen,
        Date *enroll_date,
        const string &branch_name)
        : Employee(first_name, last_name, birth_date, name, salary, isOpen, enroll_date), branch_name(branch_name) {

    this->subordinates = new vector<Employee*>();
    cout << "Manager is created. Size is: " << sizeof(Manager) << endl;

}

Manager::Manager(Manager& manager) : Employee(manager) {
    this->subordinates = new vector<Employee*>();
    cout << "Manager copy constructor" << endl;
}

Manager::Manager() {
    cout << "Manager default constructor. Size is: " << sizeof(Manager) << endl;
}

Manager::~Manager() {
    delete subordinates;
    cout << "Manager is deleted" << endl;
}

void Manager::add_suboridnate(Employee *employee) {
    this->subordinates->push_back(employee);
}

void Manager::show() {
    cout << "This is Manager: ";
    display();
}


void Manager::display() {
    Employee::display();
    cout << "Branch name: " << branch_name << endl;
    cout << "Subordinates:" << endl;
    for (auto subordinate : *subordinates) {
        cout << subordinate->get_first_name() << " " << subordinate->get_last_name() << endl;
    }
}

void Manager::display(int min_number_of_subordinates) {
    cout << "Disaplay manager if it has subordinates more that " << min_number_of_subordinates << endl;
    if (this->subordinates->size() >= min_number_of_subordinates) {
        display();
    }
}

const vector<Employee*> &Manager::get_subordinates() const {
    return *subordinates;
}

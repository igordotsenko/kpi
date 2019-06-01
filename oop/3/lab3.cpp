
#include "Person.h"
#include "Position.h"
#include "Employee.h"
#include "Manager.h"

void print_header(const string header) {
    cout << endl;
    cout << "******************************" << endl;
    cout << header << endl;
    cout << "******************************" << endl;
    cout << endl;
}

int main() {

    print_header("Create new employee: ");
    Employee* employee = new Employee("John", "Smith", new Date(1990, 1, 1), "Operator", 300, true, new Date(2018, 2,2));

    print_header("Copy existing employee: ");
    Employee* employee_2 = new Employee(*employee);

    print_header("Create default employee: ");
    Employee* default_employee = new Employee();

    print_header("Create manager: ");
    Manager* manager = new Manager("Best", "Manager", new Date(1980, 6, 15), "Manager", 1000, false, new Date(2010, 1, 1), "Operations");
    manager->add_suboridnate(employee);
    manager->add_suboridnate(employee_2);
    manager->add_suboridnate(default_employee);

    Employee* employees[] = {employee, employee_2, default_employee, manager};

    print_header("Show all employees and manager (runtime polymorphism): ");
    print_header("Employee: ");
    employees[0]->show();

    print_header("Employee copy: ");
    employees[1]->show();

    print_header("Default employee: ");
    employees[2]->show();

    print_header("Manager: ");
    employees[3]->show();

    print_header("`Display` usage with different params (compile time polymorphism): ");
    print_header("Show all employees with salary > 100: ");
    for (auto e : employees) {
        e->Position::display(100.0);
        cout << endl;
        cout << "###" << endl;
        cout << endl;
    }

    print_header("`Display` usage with different params (compile time polymorphism): ");
    print_header("Show all employees whose position is open: ");
    for (auto e : employees) {
        e->Position::display(true);
        cout << endl;
        cout << "###" << endl;
        cout << endl;
    }


    print_header("Delete employee");
    delete employee;
    print_header("Delete employee copy");
    delete employee_2;
    print_header("Delete default employee");
    delete default_employee;
    print_header("Delete manager");
    delete manager;
}

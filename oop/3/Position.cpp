#include "Position.h"

Position::Position(const string &name, double salary, bool isOpen) : title(name), salary(salary), isOpen(isOpen) {
    cout << "Position is created. Size is: " << sizeof(Position) << endl;
}

Position::Position(const Position &position): Position(position.title, position.salary, position.isOpen) {
    cout << "Position copy constructor" << endl;
}

Position::Position() : Position("default_title", 0, false) {
    cout << "Position default constructor" << endl;
}

Position::~Position() {
    cout << "Position is deleted" << endl;
}

void Position::show() {
    cout << "This is Position: ";
    display();
}

void Position::display() {
    cout << " Title: " << title << " Salary: " << salary << " Is_open: " << isOpen << endl;
}

void Position::display(double minSalary) {
    cout << "Display position if minSalary = " << minSalary << endl;
    if (salary >= minSalary) {
        display();
    }
}

void Position::display(bool isOpen) {
    cout << "Display position if is open = " << isOpen << endl;
    if (this->isOpen == isOpen) {
        display();
    }
}

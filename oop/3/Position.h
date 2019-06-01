#ifndef UNTITLED_POSITION_H
#define UNTITLED_POSITION_H

#include <string>
#include <ostream>
#include "Showable.h"

using namespace std;

class Position : public virtual Showable {
private:
    string title;
    double salary;
    bool isOpen;

public:
    Position(const string &name, double salary, bool isOpen);
    Position(const Position& position);
    Position();

    virtual ~Position();

public:
    virtual void show();
    virtual void display();
    void display(double minSalary);
    void display(bool isOpen);
};


#endif //UNTITLED_POSITION_H

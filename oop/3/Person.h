#ifndef UNTITLED_PERSON_H
#define UNTITLED_PERSON_H

#include <string>
#include <ostream>
#include "../2/Date.h"
#include "Showable.h"

using namespace std;

class Person : public virtual Showable {
private:
    string first_name;
    string last_name;
    Date* birth_date;

public:
    Person();
    Person(const string &first_name, const string &last_name, Date *birth_date);
    Person(Person& person);

    virtual ~Person();


    virtual void show();
    virtual void display();
    void display(Date& min_birth_date);

    const string &get_first_name() const;

    const string &get_last_name() const;

    friend ostream &operator<<(ostream &os, const Person &person);
};


#endif //UNTITLED_PERSON_H

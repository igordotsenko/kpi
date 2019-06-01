
#include "Person.h"

Person::Person(const string &first_name, const string &last_name, Date *birth_date) : first_name(first_name),
                                                                                      last_name(last_name),
                                                                                      birth_date(birth_date) {
    cout << "Person is created: " << this << " . Size is: " << sizeof(Person)<< endl;
}

Person::Person() : Person("default_name", "default_last_name", new Date(2000, 1, 1)) {
    cout << "Person default constructor: " << this << endl;
}

Person::Person(Person &person): Person(person.first_name, person.last_name, new Date(*person.birth_date)) {
    cout << "Person copy constructor: " << this << endl;
}

Person::~Person() {
    delete birth_date;
    cout << "Person is deleted" << endl;
}

void Person::show() {
    cout << "This is Person: ";
    display();
}

const string &Person::get_first_name() const {
    return first_name;
}

const string &Person::get_last_name() const {
    return last_name;
}

void Person::display() {
    cout << first_name << " " << last_name << " birth_date: " << *birth_date << endl;
}



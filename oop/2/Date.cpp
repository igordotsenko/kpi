//
// Created by Igor on 5/30/19.
//

#include "Date.h"

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.year << "/" << date.month << "/" << date.date;
    return os;
}

Date::Date(int year, int month, int date) {
    // TODO implement validation
    this->year = year;
    this->month = month;
    this->date = date;
}

Date::Date(Date& another) {
    this->year = another.year;
    this->month = another.month;
    this->date = another.date;
}

Date::Date() {}


Date::operator char*() {
    stringstream ss;
    ss << *this;

    string s = ss.str();
    char* ar = new char [s.length()+1];
    strcpy(ar, s.c_str());
    return ar;
}

int Date::get_year() const {
    return year;
}

int Date::get_month() const {
    return month;
}

int Date::get_date() const {
    return date;
}


void Date::serialize(ofstream& fout) {
    fout.write((char*) this, sizeof(Date));
}

void Date::deserialize(ifstream& fin) {
    fin.read((char*) this, sizeof(Date));

}


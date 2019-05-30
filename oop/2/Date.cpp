//
// Created by Igor on 5/30/19.
//

#include "Date.h"

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << "year: " << date.year << " month: " << date.month << " date: " << date.date;
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


Date::operator char*() {
    stringstream ss;
    ss << year << "/" << month << "/" << date;

    string s = ss.str();
    char* ar = new char [s.length()+1];
    strcpy(ar, s.c_str());
    return ar;
}


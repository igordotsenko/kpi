//
// Created by Igor on 5/30/19.
//

#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H


#include <ostream>
#include <string>
#include <sstream>



using namespace std;
class Date {
private:
    int year;
    int month;
    int date;

    void validate_year();
    void validate_month();
    void validate_date();

public:
    Date(int year, int month, int date);
    Date(Date& another);

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    operator char*();
};


#endif //UNTITLED_DATE_H

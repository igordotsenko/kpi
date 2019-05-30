//
// Created by Igor on 5/30/19.
//

#ifndef UNTITLED_ENTERPRISE_H
#define UNTITLED_ENTERPRISE_H

#include "Date.h"
#include <string>
#include <ostream>
#include <sstream>
#include <iostream>

using namespace std;

enum EnterpriseType {
    PRIVATE,
    PUBLIC_STOCK,
    PRIVATE_STOCK,
    STATE,
    LIMITED

};

class Enterprise {
private:
    EnterpriseType type;
    string name;
    Date* establishing_date;
    int workers_count;
    double assets;

    string type_to_string(EnterpriseType enterpriseType) const;

public:
    // TODO copy constr, default
    Enterprise(EnterpriseType type, const string &name, Date* establishing_date, int workers_count, double assets);
    Enterprise(Enterprise& another);
    Enterprise();

    string type_to_string() const;

    EnterpriseType get_type() const;
    const string &get_name() const;
    Date *get_establishing_date() const;
    int get_workers_count() const;
    double get_assets() const;

    friend void operator +=(Enterprise& first, Enterprise& second);
    friend Enterprise* operator +(Enterprise& first, Enterprise& second);
    operator char*();
    friend void operator <<(Enterprise& enterprise, int workers_to_add);
    friend ostream &operator<<(ostream &os, const Enterprise &enterprise);
    virtual ~Enterprise();
};


#endif //UNTITLED_ENTERPRISE_H

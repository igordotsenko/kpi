//
// Created by Igor on 5/30/19.
//

#include "Enterprise.h"

using namespace std;

Enterprise::Enterprise(
        EnterpriseType type,
        const string &name,
        Date* establishing_date,
        int workers_count,
        double assets)
        :
        type(type), name(name), establishing_date(establishing_date), workers_count(workers_count), assets(assets) {

    cout << "Created enterprise: " << *this << endl;
}

Enterprise::Enterprise(Enterprise& another) {
    type = another.type;
    name = another.name;
    establishing_date = new Date(*another.establishing_date);
    workers_count = another.workers_count;
    assets = another.assets;
    cout << "Copied enterprise: " << *this << endl;
}

Enterprise::Enterprise() {
    type = PRIVATE;
    name = "default";
    establishing_date = new Date(2000, 1, 1);
    workers_count = 100;
    assets = 999.99;
    cout << "Created default enterprise: " << *this << endl;
}

Enterprise::~Enterprise() {
    cout << "Deleting enterprise: " << *this << endl;
    delete establishing_date;
}


Enterprise::operator char*() {
    stringstream ss;

    ss << *this;

    string s = ss.str();
    char* ar = new char [s.length()+1];
    strcpy(ar, s.c_str());
    return ar;
}

string Enterprise::type_to_string(EnterpriseType enterpriseType) const {
    switch (enterpriseType) {
        case PRIVATE:   return "PRIVATE";
        case PUBLIC_STOCK:   return "PUBLIC_STOCK";
        case PRIVATE_STOCK: return "PRIVATE_STOCK";
        case STATE: return "STATE";
        case LIMITED: return "LIMITED";
        default:      return "[Unknown]";
    }
}

string Enterprise::type_to_string() const {
    return type_to_string(type);
}

ostream &operator<<(ostream &os, const Enterprise &enterprise) {
    os << "type: " << enterprise.type_to_string(enterprise.type) << " name: " << enterprise.name << " establishing_date: "
       << *enterprise.establishing_date << " workers_count: " << enterprise.workers_count << " assets: "
       << enterprise.assets;
    return os;
}

Enterprise* operator+(Enterprise &first, Enterprise &second) {
    return new Enterprise(first.type, first.name, first.establishing_date,
            first.workers_count + second.workers_count,
            first.assets + second.assets);
}

void operator+=(Enterprise &first, Enterprise &second) {
    first.assets += second.assets;
    first.workers_count += second.workers_count;
}

void operator<<(Enterprise &enterprise, int workers_to_add) {
    enterprise.workers_count += workers_to_add;
}

EnterpriseType Enterprise::get_type() const {
    return type;
}

const string &Enterprise::get_name() const {
    return name;
}

Date *Enterprise::get_establishing_date() const {
    return establishing_date;
}

int Enterprise::get_workers_count() const {
    return workers_count;
}

double Enterprise::get_assets() const {
    return assets;
}



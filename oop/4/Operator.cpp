#include "Operator.h"

Operator::Operator(const string &name, const string &last_name, Date *birthday) : name(name), last_name(last_name),
                                                                                  birthday(birthday) {}
Operator::Operator() {
    birthday = new Date();
}


Operator::~Operator() {
    delete birthday;
}

const string &Operator::get_name() const {
    return name;
}

const string &Operator::get_last_name() const {
    return last_name;
}

Date *Operator::get_birthday() const {
    return birthday;
}

void Operator::serialize(ofstream &fout) {
    fout.write((char*) &name, sizeof(string));
    fout.write((char*) &name, sizeof(string));
    birthday->serialize(fout);
}

void Operator::deserialize(ifstream &fin) {
    fin.read((char*) &name, sizeof(string));
    fin.read((char*) &name, sizeof(string));
    birthday->deserialize(fin);
}


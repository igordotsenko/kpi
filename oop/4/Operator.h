#ifndef UNTITLED_OPERATOR_H
#define UNTITLED_OPERATOR_H

#include <string>
#include "../2/Date.h"
#include <fstream>


using namespace std;

class Operator {
private:
    string name;
    string last_name;
    Date* birthday;

public:
    Operator(const string &name, const string &last_name, Date *birthday);

    Operator();

    virtual ~Operator();

    const string &get_name() const;
    const string &get_last_name() const;
    Date *get_birthday() const;

    void serialize(ofstream &fout);
    void deserialize(ifstream &fin);

    // TODO cout table
};


#endif //UNTITLED_OPERATOR_H

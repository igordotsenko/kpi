#ifndef UNTITLED_CHECKOUT_H
#define UNTITLED_CHECKOUT_H


#include <ostream>
#include "Operator.h"
#include "Fuel.h"
#include <fstream>


class Checkout {
private:
    Operator* anOperator;
    Fuel* fuel;
    double amount;
    Date* checkout_date;
    double total_price;

public:
    Checkout(Operator *anOperator, Fuel *fuel, double amount, Date *checkout_date);

    Checkout();

    virtual ~Checkout();

    Operator *get_an_operator() const;
    Fuel *get_fuel() const;
    double get_amount() const;
    Date *get_checkout_date() const;
    double get_total_price() const;
    void serialize(ofstream &fout);
    void deserialize(ifstream &fin);

    // TODO table cout
    friend ostream &operator<<(ostream &os, const Checkout &checkout);
};


#endif //UNTITLED_CHECKOUT_H

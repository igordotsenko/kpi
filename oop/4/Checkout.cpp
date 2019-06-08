#include "Checkout.h"

Checkout::Checkout(Operator *anOperator, Fuel *fuel, double amount, Date *checkout_date) : anOperator(anOperator),
                                                                                           fuel(fuel), amount(amount),
                                                                                           checkout_date(
                                                                                                   checkout_date) {
    this->total_price = fuel->get_price_per_liter() * amount;
}

Checkout::Checkout(): Checkout(new Operator(), new Fuel(), 0, new Date()) {}


Checkout::~Checkout() {
    delete anOperator;
    delete fuel;
    delete checkout_date;
}

Operator *Checkout::get_an_operator() const {
    return anOperator;
}

Fuel *Checkout::get_fuel() const {
    return fuel;
}

double Checkout::get_amount() const {
    return amount;
}

Date *Checkout::get_checkout_date() const {
    return checkout_date;
}

double Checkout::get_total_price() const {
    return total_price;
}

ostream &operator<<(ostream &os, const Checkout &checkout) {
    os << "anOperator: " << checkout.anOperator << " fuel: " << checkout.fuel << " amount: " << checkout.amount
       << " checkout_date: " << checkout.checkout_date << " total_price: " << checkout.total_price;
    return os;
}

void Checkout::serialize(ofstream &fout) {
    anOperator->serialize(fout);
    fuel->serialize(fout);
    fout.write((char *) &amount, sizeof(double));
    checkout_date->serialize(fout);
    fout.write((char *) &total_price, sizeof(double));
}

void Checkout::deserialize(ifstream &fin) {
    anOperator->deserialize(fin);
    fuel->deserialize(fin);
    fin.read((char *) &amount, sizeof(double));
    checkout_date->deserialize(fin);
    fin.read((char *) &total_price, sizeof(double));
}


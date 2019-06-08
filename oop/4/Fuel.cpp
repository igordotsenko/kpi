#include "Fuel.h"

Fuel::Fuel(FuelType type, double price_per_liter) : type(type), price_per_liter(price_per_liter) {}
Fuel::Fuel() {}

FuelType Fuel::get_type() const {
    return type;
}

double Fuel::get_price_per_liter() const {
    return price_per_liter;
}

void Fuel::serialize(ofstream& fout) {
    fout.write((char*) this, sizeof(Fuel));
}

void Fuel::deserialize(ifstream& fin) {
    fin.read((char*) this, sizeof(Fuel));
}



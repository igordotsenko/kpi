
#ifndef UNTITLED_FUEL_H
#define UNTITLED_FUEL_H

#include <fstream>

using namespace std;

enum FuelType {
    AI_92,
    AI_95,
    AI_98,
    DIESEL
};

class Fuel {
private:
    FuelType type;
    double price_per_liter;

public:
    Fuel(FuelType type, double price_per_liter);
    Fuel();

    FuelType get_type() const;
    double get_price_per_liter() const;

    void serialize(ofstream& fout);
    void deserialize(ifstream& fin);

    // TODO table output
};


#endif //UNTITLED_FUEL_H

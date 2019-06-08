#ifndef UNTITLED_DAILYBALANCE_H
#define UNTITLED_DAILYBALANCE_H


#include "Checkout.h"
#include <cmath>
#include <iostream>
#include "Container.h"

class DailyBalance : public Container<Checkout> {
public:
    DailyBalance(int initial_capacity) : Container(initial_capacity) {}

    virtual ~DailyBalance();
    void write_bin();
    void read_bin();

    template <typename T>
    T calculate_deviation(T input) {
        double sum = 0;
        for (int i = 0; i < size(); i++) {
            sum += (*this)[i]->get_total_price();
        }

        double mean = sum / size();
        double variance = 0;
        for (int i = 0; i < size(); i++) {
            variance += pow((*this)[i]->get_total_price() - mean, 2);
        }

        variance /= size();
        return sqrt(variance);
    }
};


#endif //UNTITLED_DAILYBALANCE_H

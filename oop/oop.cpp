#include <iostream>
#include "1/Function.h"
#include <vector>


void showlist(std::vector<double> g) {
    vector<double> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it;
    cout << '\n';
}

int main() {
    auto function = new Function(1, 6, 0.5, 5.5, 0.25);
    cout << "Single value: " << function->getValue(1) << endl;

    auto values = function->getAllValues();
    function->tab();

    cout << "S1: " << function -> calculate_s1() << endl;
    cout << "S2: " << function -> calculate_s2() << endl;

    function->print_rnd();
}

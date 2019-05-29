#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Function.h"
#include <iomanip>
#include <sstream>
#include <random>

std::random_device Function::rd;
std::mt19937 Function::rng(rd());

Function::Function(double a, double b, double x1, double x2, double dx) : a(a), b(b), x1(x1), x2(x2), dx(dx) {}
Function::Function() : Function(1, 6, 0.5, 5.5, 0.25) {}

double Function::getValue(double x) {
    if (x >= 2) {
        return -1*a * x*x - b;
    } else {
        return (x-b)/x;
    }
}

vector<double>* Function::getAllValues() {
    int numberOfValues = getNumberOfValues();
    auto values = new vector<double>();
    values->reserve(numberOfValues);
    for (int i = 0; i < numberOfValues; i++) {
        values->push_back(getValue(getX(i)));
    }
    return values;
}

void Function::tab() {
    int numberOfValues = getNumberOfValues();
    printf("┌─────┬──────────┐\n");
    printf("│  x  │   f(x)   │\n");
    for (int i = 0; i < numberOfValues; i++) {
        double x = getX(i);
        printf("│%-5.2f│%-10.5g│\n", x, getValue(x));
    }
    printf("└─────┴──────────┘\n");
}

int Function::getNumberOfValues() {
    return abs((int)((x2-x1)/dx)+1);
}

double Function::getX(int index) {
    return x1+dx*index;
}

double Function::calculate_s2(vector<double>& values) {
    int negative_numbers_count = 0;
    double negative_numbers_sum = 0;

    for (auto it = values.begin(); it != values.end(); ++it) {
        auto value = *it;
         if (value < 0) {
             negative_numbers_count++;
             negative_numbers_sum += value;
         }
    }

    return negative_numbers_count > 0 ? negative_numbers_sum / negative_numbers_count : 0;
}

double Function::calculate_s1() {
    vector<double>* values = getAllValues();
    double min = values->at(0);
    for (int i = 2; i < values->size(); i += 2) {
        double value = values->at(i);
        if (value < min) {
            min = value;
        }
    }
    delete values;
    return min;
}

double Function::calculate_s2() {
    vector<double>* values = getAllValues();
    double s2 = calculate_s2(*values);
    delete(values);
    return s2;
}

void Function::print_rnd() {
    int n = getNumberOfValues();
    double rnd[n];
    double s1 = calculate_s1();
    double s2 = calculate_s2();
    double max = s1 > s2 ? s1 : s2;
    double min = max == s1 ? s2 : s1;
    double step = abs(max)*delta;

    int number_of_steps = (int)(abs(max-min)/step);
    std::uniform_int_distribution<int> uni(0, number_of_steps);
    for (int i = 0; i < n; i++) {
        int random = uni(rng);
        double rnd_el = min + random*step;
        rnd[i] = rnd_el;
    }

    char line[]= "──────────";
    printf("┌%s┬%s┐\n", line, line);
    printf("│%-10s│%-10.2f│\n", "s1", s1);
    printf("│%-10s│%-10.2f│\n", "s2", s2);
    printf("│%s│%s│\n", line, line);
    for (int i = 0; i < n; i++) {
        printf("│%-10d│%-10.2f│\n", i, rnd[i]);
    }
    printf("└%s┴%s┘\n", line, line);
}

void Function::print() {
    vector<double>* values = getAllValues();
    int n = getNumberOfValues();
    double max = values->at(0);
    double min = values->at(0);

    for (int i = 1; i < n; i++) {
        double value = values->at(i);
        if (value < min) {
            min = value;
        } else if (value > max) {
            max = value;
        }
    }

    int transformed[n];
    for (int i = 0; i < n; i++) {
        transformed[i] = (A * (values->at(i)-min)/(max-min));
    }

    for (int i = 0; i < n; i++) {
        int t = transformed[i];
        for (int j = 0; j < t; j++) {
            cout << "░";
        }
        cout << endl;
    }

    delete values;
}

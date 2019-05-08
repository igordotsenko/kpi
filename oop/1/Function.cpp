#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Function.h"
#include <iomanip>
#include <sstream>

const std::string Function::X_CELL_HEADER = "x";
const std::string Function::VALUE_CELL_HEADER = "f(x)";

Function::Function(double a, double b, double x1, double x2, double dx) : a(a), b(b), x1(x1), x2(x2), dx(dx) {}
Function::Function() : a(1), b(6), x1(0.5), x2(5.5), dx(0.25) {}

double Function::getValue(double x) {
//    cout << "x = " << x << endl;
    if (x >= 2) {
//        cout << "result = " << -1*a * x*x - b << endl;
        return -1*a * x*x - b;
    } else {
//        cout << "result = " << (x-b)/x << endl;
        return (x-b)/x;
    }
}

vector<double> Function::getAllValues() {
    int numberOfValues = getNumberOfValues();
    auto values = *new vector<double>((unsigned long) numberOfValues);
    for (int i = 0; i < numberOfValues; i++) {
        values[i] = getValue(getX(i));
    }
    return values;
}

void Function::tab() {
    printTabHeader();

    int numberOfValues = getNumberOfValues();
    for (int i = 0; i < numberOfValues; i++) {
        double x = getX(i);
        printTabLine(x, getValue(x));
    }
    printTabFooter();
}

int Function::getNumberOfValues() {
    return abs((int)((x2-x1)/dx)+1);
}

double Function::getX(int index) {
    return x1+dx*index;
}

void Function::printTabHeader() {
    cout << "┌";
    printTabLineSeparator(X_CELL_CHARACTERS_COUNT);
    cout << "┬";
    printTabLineSeparator(VALUE_CELL_CHARACTERS_COUNT);
    cout << "┐" << endl;

    unsigned long left_x_spaces = (X_CELL_CHARACTERS_COUNT - X_CELL_HEADER.length()) / 2;
    unsigned long left_value_spaces = (VALUE_CELL_CHARACTERS_COUNT - VALUE_CELL_HEADER.length()) / 2;

    unsigned long right_x_spaces = X_CELL_HEADER.length() % 2 == 0 ? left_x_spaces+1 : left_x_spaces;
    unsigned long right_value_spaces = VALUE_CELL_HEADER.length() % 2 == 0 ? left_value_spaces : left_value_spaces+1;

    cout << "│" << std::string(left_x_spaces, ' ') << X_CELL_HEADER <<  std::string(right_x_spaces, ' ') << "│";
    cout << std::string(left_value_spaces, ' ') << VALUE_CELL_HEADER <<  std::string(right_value_spaces, ' ') << "│"
    << endl;

}

void Function::printTabLine(double x, double value) {
    std::ostringstream x_sting_stream;
    x_sting_stream << "│" << std::string(TAB_SPACING_INTERVAL, ' ')  << x;
    std::string left_x_cell = x_sting_stream.str();
    int a = X_CELL_CHARACTERS_COUNT;
    int b = left_x_cell.length();
    // NOTE: 2 is for stream additional symboles
    // 1 is for "│" sign
    unsigned long x_right_cell_spacing = (X_CELL_CHARACTERS_COUNT - (left_x_cell.length()-2)) + 1;

    std::ostringstream value_sting_stream;
    value_sting_stream <<  value << std::string(TAB_SPACING_INTERVAL, ' ') << "│";
    std::string right_value_cell = value_sting_stream.str();
    unsigned long value_right_cell_spacing = (VALUE_CELL_CHARACTERS_COUNT - (right_value_cell.length()-2)) + 1;

    cout << left_x_cell <<  std::string(x_right_cell_spacing, ' ') << "│"
    << std::string(value_right_cell_spacing, ' ') << right_value_cell << endl;
}

void Function::printTabFooter() {
    cout << "└";
    printTabLineSeparator(X_CELL_CHARACTERS_COUNT);
    cout << "┴";
    printTabLineSeparator(VALUE_CELL_CHARACTERS_COUNT);
    cout << "┘" << endl;
}

void Function::printTabLineSeparator(int cell_characters_total_count) {
    for (int i = 0; i < cell_characters_total_count; i++) {
        cout << "─";
    }
}

#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <random>

using namespace std;

class Function {
        public:
            static constexpr double delta = 0.04;

    Function(double a, double b, double x1, double x2, double dx);
            Function();

            double getValue(double x);
            vector<double>* getAllValues();
            void tab();
            double calculate_s1();
            double calculate_s2();
            void print_rnd();



        private:
            double a;
            double b;
            double x1;
            double x2;
            double dx;
            static std::random_device rd;
            static std::mt19937 rng;

            int getNumberOfValues();
            double getX(int index);
            void printTabHeader();
            void printTabLine(double x, double value);
            void printTabFooter();
            void printTabLineSeparator(int cell_characters_total_count);
            double calculate_s2(vector<double>& values);
};

#endif //UNTITLED_FUNCTION_H

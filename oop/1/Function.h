#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <cstdlib>
#include <list>

using namespace std;

class Function {
        public:
            static const int X_PRECISION = 3;
            static const int VALUE_PRECISION = 6;
            static const int TAB_SPACING_INTERVAL = 1;
            static const int TAB_TOTAL_SPACES_PER_CELL_COUNT = 2;
            static const int CELL_EXTRA_SPACE = 2; // 2 is for potential dot and minus
            static const int X_CELL_CHARACTERS_COUNT = X_PRECISION + TAB_TOTAL_SPACES_PER_CELL_COUNT + CELL_EXTRA_SPACE;
            static const int VALUE_CELL_CHARACTERS_COUNT = VALUE_PRECISION + TAB_TOTAL_SPACES_PER_CELL_COUNT + CELL_EXTRA_SPACE;
            static const std::string X_CELL_HEADER;
            static const std::string VALUE_CELL_HEADER;
//            static const int CELLS_SEPARATOR_CHARACTERS_COUNT = 1;

            Function(double a, double b, double x1, double x2, double dx);
            Function();

            double getValue(double x);
            vector<double> getAllValues();
            void tab();

        private:
            double a;
            double b;
            double x1;
            double x2;
            double dx;

            int getNumberOfValues();
            double getX(int index);
            void printTabHeader();
            void printTabLine(double x, double value);
            void printTabFooter();
            void printTabLineSeparator(int cell_characters_total_count);
};

#endif //UNTITLED_FUNCTION_H

#include <cstdio>
#include <cmath>
#include <algorithm>

int third_c() {
    double x_min = -1;
    double x_max = 1;
    double step = 0.1;

    for (double x_current = x_min; x_current <= x_max; x_current += step) {
        double y = 0;

        for (double k = 1; k < 30; k++) {
            y += 1 / (pow(x_current, 2) + k);
        }

        printf("x = %.1lf y = %.2lf\n", x_current, y);
    }
}

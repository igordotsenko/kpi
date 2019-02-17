#include <cstdio>
#include <cmath>

int main() {
    double a, b, x, y;

    printf("Enter x = ");
    scanf("%lf", &x);

    if (x == 4) {
        printf("Function is not determined for x = 4");
        return 0;
    }

    printf("Enter a = ");
    scanf("%lf", &a);
    printf("Enter b = ");
    scanf("%lf", &b);

    if (x < 4) {
        y = log10(fabs(a*x+b));
    } else {
        y = a*b*x;
    }

    printf("Y = %f", y);
    return 0;
}
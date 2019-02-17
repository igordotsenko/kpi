#include <cstdio>
#include <cmath>
#include <algorithm>

int first() {
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

    printf("Y = %lf\n", y);
    return 0;
}

double max(double a, double b) {
    return a > b ? a : b;
}

int digit_string_length(double digit) {
    int len = 1;

    for (int i = (int) digit; i != 0; i /= 10, len++);

    return len + 3; // also count dot and 2 digits after dot
}

int find_indent(int row_len, int value_len) {
    return row_len - value_len;
}

void print_line(int row_len) {
    printf("|");
    for (int print_len = row_len + 5; print_len > 0; print_len--) {
        printf("-");
    }
    printf("|\n");
}

void print_row(char variable_name, double value, int digit_row_len) {

    if (std::isnan(value)) {
        printf("| %c | NaN %*s |\n", variable_name, find_indent(digit_row_len, 3), "");
    } else if (!std::isfinite(value)) {
        printf("| %c | INF %*s |\n", variable_name, find_indent(digit_row_len, 3), "");
    } else {
        int indent = find_indent(digit_row_len, digit_string_length(value));
        printf("| %c | %.2lf%*s |\n", variable_name, value, indent, "");
    }
    print_line(digit_row_len);
}

double find_longest_value(double a, double x, double y) {
    return (std::isnan(y) || !std::isfinite(y)) ? max(a, x) : max(a, max(x, y));
}

int second() {
    double a, x, y;

    printf("Enter a = ");
    scanf("%lf", &a);
    printf("Enter x = ");
    scanf("%lf", &x);

    y = a*x*log10(pow(a+x, 2)) / a*x*sqrt(a*sqrt(x));

    double longest_value = find_longest_value(fabs(a), fabs(x), fabs(y));
    int digit_row_len = digit_string_length(longest_value);

    print_line(digit_row_len);
    print_row('a', a, digit_row_len);
    print_row('x', x, digit_row_len);
    print_row('y', y, digit_row_len);
}

int main() {
    second();
}



#include <cstdio>

int main() {
    char name[20];
    int birth_year;
    double temperature;

    printf("Enter you name\n");
    scanf("%20s", name);

    printf("What year did you born?\n");
    scanf("%d", &birth_year);

    printf("What's the temperature outside?\n");
    scanf("%lf", &temperature);

    printf("-------------------------------------------------------------------------------\n");
    printf("| Your name is %s | You're born in %d | Temperature outside is %.1lf |\n", name, birth_year, temperature);
    printf("-------------------------------------------------------------------------------\n");
}
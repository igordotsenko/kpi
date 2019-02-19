#include <cstdio>
#include "third_a.h"
#include "third_b.h"
#include "third_c.h"

int main(int argc, char *argv[], char *env[]) {
    if (argc < 2) {
        printf("Pass 1 or 2 or 3 to execute program\n");
        return 0;
    }

    char *option = argv[1];

    printf("Option selected: %s\n\n", option);

    switch (*option) {
        case '1':
            third_a();
            break;
        case '2':
            third_b();
            break;
        case '3':
            third_c();
            break;
        default:
            printf("Pass option 1 or 2 or 3\n");
    }
}

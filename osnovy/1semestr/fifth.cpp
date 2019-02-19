#include <cstdio>

int main(int argc, char *argv[], char *env[]) {
    for (int i = 0; i < argc; i++) {
        printf("Arg #%d: %s\n", i, argv[i]);
    }
}

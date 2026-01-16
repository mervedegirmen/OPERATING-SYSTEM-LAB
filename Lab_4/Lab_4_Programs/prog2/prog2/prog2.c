// prog2.c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("A total of %d arguments were sent to the program.\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}
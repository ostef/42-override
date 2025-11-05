#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv, char** envp) {
    int i = 0;
    char buff[100];

    fgets(buff, 100, stdin);
    int len = strlen(buff);
    while (i < len) {
        if (buff[i] >= 'A' && buff[i] <= 'Z') {
            buff[i] += 'a' - 'A';
        }
        i += 1;
    }

    printf(buff);
    exit(0);
}

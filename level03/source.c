#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void clear_stdin() {
    while (true) {
        char c = getchar();
        if (c == '\n') {
            return;
        } else if (c == 255) {
            return;
        }
    }
}

unsigned int get_unum() {
    fflush(stdout);

    unsigned int result;
    scanf("%u", result);

    clear_stdin();

    return result;
}

int decrypt(char key) {
    char hashed[28];
    strcpy(hashed, "Q}|u`sfg~sf{}|a3");

    int length = strlen(hashed);
    for (int i = 0; i < length; ++i) {
        hashed[i] ^= key;
    }

    if (!strcmp(hashed, "Congratulations!")) {
        return system("/bin/sh");
    } else {
        return puts("\nInvalid Password");
    }
}

void test(unsigned int a, unsigned int b) {
    unsigned int diff = b - a;
    switch (diff) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        decrypt(diff);
        return;
    default:
        decrypt(rand());
        return;
    }
}

int main() {
    srand(time(NULL));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");

    printf("Password:");
    unsigned int input = get_unum();
    test(input, 322424845);

    return 0;
}

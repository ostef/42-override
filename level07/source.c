#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int store_number(unsigned int *buffer) {
    printf(" Number: ");
    int number = get_unum();

    printf(" Index: ");
    int index = get_unum();

    // On ne peut pas ecrire a un index divisible par 3, ou un nombre qui commence par 0xb7
    if ((index % 3) == 0 || (number >> 24) == 0xb7) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    // Aucun bounds check, on peut donc aller chercher n'importe ou dans la stack
    buffer[index] = number;
    return 0;
}

int read_number(unsigned int *buffer) {
    printf(" Index: ");
    int index = get_unum();
    // Aucun bounds check, on peut donc aller chercher n'importe ou dans la stack
    printf(" Number at data[%u] is %u\n", index, buffer[index]);
    return 0;
}

int main(int argc, char** argv, char** envp) {
    // Reset argv
    for (int i = 0 ; argv[i] != NULL; i += 1) {
        memset(argv[i], 0, strlen(argv[i]));
    }

    // Reset env
    for (int i = 0 ; envp[i] != NULL; i += 1) {
        memset(envp[i], 0, strlen(envp[i]));
    }

    unsigned int storage[100];
    memset(&storage, 0, sizeof(unsigned int) * 100);

    char input[20];

    puts(
"----------------------------------------------------\n"
"  Welcome to wil's crappy number storage service!\n"
"----------------------------------------------------\n"
" Commands:\n"
"    store - store a number into the data storage\n"
"    read  - read a number from the data storage\n"
"    quit  - exit the program\n"
"----------------------------------------------------\n"
"   wil has reserved some storage :>\n"
"----------------------------------------------------\n"
    );

    while (true) {
        printf("Input command: ");

        fgets(input, 20, stdin);
        input[strlen(input) - 1] = 0;

        int number = 1;
        if (!memcmp(input, "store", 5)) {
            number = store_number(storage);
        } else if (!memcmp(input, "read", 4)) {
            number = read_number(storage);
        } else if (!memcmp(input, "quit", 4)) {
            return 0;
        }

        if (number) {
            printf(" Failed to do %s command\n", input);
        } else {
            printf(" Completed %s command successfully\n", input);
        }
    }
}

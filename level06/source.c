#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/ptrace.h>

int auth(char *str, unsigned int key) {
    str[strcspn(str, "\n")] = 0;
    unsigned int len = strnlen(str, 32);
    if (len <= 5) {
        return 1;
    } else if (ptrace(PTRACE_TRACEME) == -1) {
        puts("\x1b[32m.---------------------------.");
        puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1b[32m\'---------------------------\'");

        return 1;
    } else {
        unsigned int hash = (str[3] ^ 0x1337) + 0x5eeded;
        for (unsigned int i = 0; i < len; ++i) {
            if (str[i] < ' ') {
                return 1;
            }

            hash += (hash ^ (unsigned int)str[i]) % 0x539;
        }

        printf("%u\n", hash);

        return (key == hash ? 0 : 1);
    }
}

int main() {
    char buff[32];
    unsigned int key;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    printf("-> Enter Login: ");
    fgets(buff, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    printf("-> Enter Serial: ");
    scanf("%u", &key);

    if (auth(buff, key) == 0) {
        puts("Authenticated!");
        system("/bin/sh");

        return 0;
    }

    return 1;
}

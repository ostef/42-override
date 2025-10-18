#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[100];

int32_t verify_user_name() {
    puts("verifying username....\n");
    return memcmp(a_user_name, "dat_wil", 7u) != 0;
}

int32_t verify_user_pass(const void *a1) {
    return memcmp(a1, "admin", 5u) != 0;
}

int32_t main(int32_t argc, char** argv, char** envp) {
    char pass[64];

    memset(pass, 0, sizeof(pass));
    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);

    if (verify_user_name()) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(pass, 100, stdin); // buffer is 64 bytes but we read at most 100 bytes. Potential buffer overrun exploit

    int32_t pass_result = verify_user_pass(pass);

    // Always true!
    if (pass_result || !pass_result) {
        puts("nope, incorrect password...\n");
        return 1;
    }

    return 0;
}
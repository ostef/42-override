#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char message[140]; // offset 0
    char username[40]; // offset 140
    int length;        // offset 180
} Struct;

int64_t secret_backdoor() {
    char buf[128];
    fgets(buf, 128, stdin);
    return system(buf);
}

char* set_msg(Struct* result) {
    char buf[1024] = {0};

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(buf, 1024, stdin);

    return strncpy(result->message, buf, result->length);
}

int64_t set_username(Struct *result) {
    char buf[140] = {0};

    puts(">: Enter your username");
    printf(">>: ");
    fgets(buf, 128, stdin);

    // On ecrit jusqu'a 40 INCLUS, donc on peut ecrire le premier byte de length!
    for (int32_t i = 0; i <= 40; i += 1) {
        if (!buf[i]) {
            break;
        }

        result->username[i] = buf[i];
    }

    return printf(">: Welcome, %s", result->username);
}

int64_t handle_msg() {
    // push %rbp -> 8 bytes
    // sub 0xc0,%rsp -> 192 bytes
    // RIP -> 200 bytes

    Struct result = {0};
    result.length = 140;

    set_username(&result);
    set_msg(&result);

    return puts(">: Msg sent!");
}


int32_t main(int32_t argc, char** argv, char** envp) {
    puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |"
    "--------------------------------------------");
    handle_msg();
    return 0;
}

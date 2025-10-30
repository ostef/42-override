#include <stdio.h>
#include <string.h>

int main(int argc, const char **argv, const char **envp) {
    char s2[100];
    char ptr[48];
    char s[100];
    int bytes_read = 0;
    FILE *stream = NULL;

    memset(s, 0, sizeof(s));
    memset(ptr, 0, 41);
    memset(s2, 0, sizeof(s2));

    stream = fopen("/home/users/level03/.pass", "r");
    if (!stream) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    bytes_read = fread(ptr, 1, 41, stream);
    ptr[strcspn(ptr, "\n")] = 0;

    if (bytes_read != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }

    fclose(stream);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(s, 100, stdin);
    s[strcspn(s, "\n")] = 0;

    printf("--[ Password: ");
    fgets(s2, 100, stdin);
    s2[strcspn(s2, "\n")] = 0;

    puts("*****************************************");

    if (strncmp(ptr, s2, 41)) {
        printf(s); // Potential format string attack (%x will print the stack)
        puts(" does not have access!");
        exit(1);
    }

    printf("Greetings, %s!\n", s);
    system("/bin/sh");

    return 0;
}

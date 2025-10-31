#include <stdio.h>
#include <string.h>

int main(int argc, const char **argv, const char **envp) {
    char pass_input[100];
    char pass[48];
    char username[100];
    int bytes_read = 0;
    FILE *stream = NULL;

    memset(username, 0, sizeof(username));
    memset(pass, 0, 41);
    memset(pass_input, 0, sizeof(pass_input));

    stream = fopen("/home/users/level03/.pass", "r");
    if (!stream) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    bytes_read = fread(pass, 1, 41, stream);
    pass[strcspn(pass, "\n")] = 0;

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
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("--[ Password: ");
    fgets(pass_input, 100, stdin);
    pass_input[strcspn(pass_input, "\n")] = 0;

    puts("*****************************************");

    if (strncmp(pass, pass_input, 41)) {
        printf(username); // Potential format string attack (%p will print 8 bytes of the stack)
        puts(" does not have access!");
        exit(1);
    }

    printf("Greetings, %s!\n", username);
    system("/bin/sh");

    return 0;
}

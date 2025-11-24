#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int64_t log_wrapper(FILE* arg1, char* arg2, char* arg3)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    char var_118[0x108];
    strcpy(&var_118, arg2);
    int64_t i = -1;
    char (* rdi_1)[0x108] = &var_118;

    while (i)
    {
        bool cond:0_1 = 0 != *rdi_1;
        rdi_1 = &(*rdi_1)[1];
        i -= 1;

        if (!cond:0_1)
            break;
    }

    int64_t i_1 = -1;
    char (* rdi_2)[0x108] = &var_118;

    while (i_1)
    {
        bool cond:1_1 = 0 != *rdi_2;
        rdi_2 = &(*rdi_2)[1];
        i_1 -= 1;

        if (!cond:1_1)
            break;
    }

    snprintf(&var_118[~i_1 - 1], 0xfe - (~i - 1), arg3);
    var_118[strcspn(&var_118, "\n")] = 0;
    fprintf(arg1, "LOG: %s\n", &var_118, "LOG: %s\n");
    int64_t result = rax ^ *(fsbase + 0x28);

    if (!result)
        return result;

    __stack_chk_fail();
    /* no return */
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    char buf = 0xff;
    int32_t var_80 = 0xffffffff;

    if (argc != 2)
        printf("Usage: %s filename\n", *argv);

    FILE* rax_4 = fopen("./backups/.log", "w");

    if (!rax_4)
    {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
        /* no return */
    }

    log_wrapper(rax_4, "Starting back up: ", argv[1]);
    FILE* fp = fopen(argv[1], "r");

    if (!fp)
    {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
        /* no return */
    }

    int64_t file;
    __builtin_strncpy(&file, "./backups/", 11);
    int64_t i = -1;
    int64_t* rdi_2 = &file;

    while (i)
    {
        bool cond:0_1 = 0 != *rdi_2;
        rdi_2 += 1;
        i -= 1;

        if (!cond:0_1)
            break;
    }

    strncat(&file, argv[1], 0x63 - (~i - 1));
    int32_t fd = open(&file, 0xc1, 0x1b0);

    if (fd < 0)
    {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
        /* no return */
    }

    while (true)
    {
        buf = fgetc(fp);

        if (buf == 0xff)
            break;

        write(fd, &buf, 1);
    }

    log_wrapper(rax_4, "Finished back up ", argv[1]);
    fclose(fp);
    close(fd);

    if (rax == *(fsbase + 0x28))
        return 0;

    __stack_chk_fail();
    /* no return */
}

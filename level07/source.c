#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int store_number(uint32_t *buffer) {
    printf(" Number: ");
    int32_t number = get_unum();

    printf(" Index: ");
    int32_t index = get_unum();

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

int read_number(uint32_t *buffer) {
    printf(" Index: ");
    int32_t index = get_unum();
    // Aucun bounds check, on peut donc aller chercher n'importe ou dans la stack
    printf(" Number at data[%u] is %u\n", index, buffer[index]);
    return 0;
}

int32_t main(int32_t argc, char** argv, char** envp) {
    void* gsbase;
    int32_t eax_2 = *(gsbase + 0x14);
    int32_t var_2c_1;
    __builtin_memset(&var_2c_1, 0, 24);

    uint32_t buffer[100];
    __builtin_memset(&buffer, 0, sizeof(uint32_t) * 100);

    int32_t var_1dc;
    size_t fp;

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
        printf("Input command: ", var_1dc, fp);
        int32_t var_2c_2 = 1;
        fp = stdin;
        int32_t buf;
        fgets(&buf, 0x14, fp);
        int32_t i_2 = 0xffffffff;
        int32_t* edi_3 = &buf;

        while (i_2) {
            bool cond:6_1 = 0 != *edi_3;
            edi_3 += 1;
            i_2 -= 1;

            if (!cond:6_1) {
                break;
            }
        }

        bool c_1 = ~i_2 - 1 < 1;
        bool z_1 = ~i_2 == 2;
        *(&buf + ~i_2 - 2) = 0;
        int32_t i_3 = 5;
        int32_t* esi_1 = &buf;
        void* const edi_4 = "store";

        while (i_3) {
            char temp1_1 = *esi_1;
            char temp2_1 = *edi_4;
            c_1 = temp1_1 < temp2_1;
            z_1 = temp1_1 == temp2_1;
            esi_1 += 1;
            edi_4 += 1;
            i_3 -= 1;

            if (!z_1) {
                break;
            }
        }

        bool c_2 = false;
        bool z_2 = !((!z_1 && !c_1) - c_1);

        if (!z_2) {
            int32_t i_4 = 4;
            int32_t* esi_2 = &buf;
            void* const edi_5 = "read";

            while (i_4) {
                char temp3_1 = *esi_2;
                char temp4_1 = *edi_5;
                c_2 = temp3_1 < temp4_1;
                z_2 = temp3_1 == temp4_1;
                esi_2 += 1;
                edi_5 += 1;
                i_4 -= 1;

                if (!z_2) {
                    break;
                }
            }

            bool c_3 = false;
            bool z_3 = !((!z_2 && !c_2) - c_2);

            if (!z_3) {
                int32_t i_5 = 4;
                int32_t* esi_3 = &buf;
                void* const edi_6 = "quit";

                while (i_5) {
                    char temp5_1 = *esi_3;
                    char temp6_1 = *edi_6;
                    c_3 = temp5_1 < temp6_1;
                    z_3 = temp5_1 == temp6_1;
                    esi_3 += 1;
                    edi_6 += 1;
                    i_5 -= 1;

                    if (!z_3) {
                        break;
                    }
                }

                if (!((!z_3 && !c_3) - c_3)) {
                    if (eax_2 == *(gsbase + 0x14)) {
                        return 0;
                    }

                    __stack_chk_fail();
                    /* no return */
                }
            } else {
                read_number(&buffer);
                var_2c_2 = 0;
            }
        } else {
            var_2c_2 = store_number(&buffer);
        }

        if (!var_2c_2) {
            var_1dc = &buf;
            printf(" Completed %s command successfully\n", var_1dc);
        } else {
            var_1dc = &buf;
            printf(" Failed to do %s command\n", var_1dc);
        }

        __builtin_memset(&buf, 0, 0x14);
    }
}

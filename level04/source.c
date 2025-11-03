#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <sys/user.h>
#include <linux/prctl.h>
#include <unistd.h>

#define EAX offsetof(struct user_regs_struct, orig_eax); // 32-bit registers

int main(int argc, char **argv) {
    // EIP pushed on the stack  <- byte 156
    // argc (4 bytes)
    // argv (4 bytes)
    // envp (4 bytes)
    int iVar1;
    char *pcVar2;
    // align (3 bytes)
    char bVar3;
    unsigned int local_a4;
    char local_a0 [128];
    unsigned int local_20;
    unsigned int local_1c;
    long local_18;
    int local_14;

    memset(buf, 0, 128);
    child_pid = fork();

    if (child_pid == 0) {
        prctl(PR_SET_PDEATHSIG, 1); // Set the signal to receive upon the parent's death
        ptrace(PTRACE_TRACEME);
        puts("Give me some shellcode, k");
        gets(buf);
    } else {
        while (true) {
            int stat_loc = 0;
            wait(&stat_loc);

            if ((stat_loc & 0x7f) == 0 || ((stat_loc & 0x7f) + 1) >> 1 > 0) {
                puts("child is exiting...");
                break;
            }

            // PTRACE_PEEKUSER reads the registers of the tracee
            // This makes sure that register orignal_eax never has value 11
            // If it is not the case the child is killed
            if (ptrace(PTRACE_PEEKUSER, child_pid, EAX) != 11) {
                continue;
            }

            puts("no exec() for you");
            kill(child_pid, 9);
            break;
        }
    }

    return 0;
}

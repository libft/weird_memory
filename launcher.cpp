#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <dlfcn.h>
#include <mach/mach.h>
#include "osxinj/injector.h"

int main(int argc, char* argv[], char* envp[])
{
    if (argc < 2)
    {
        printf("Usage: %s [path] ([arguments...])\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if (pid != 0)
    {
        kill(pid, SIGSTOP);
        usleep(500000);

        Injector inj;
        inj.inject(pid, "libbootstrap.dylib");

        usleep(500000);
        kill(pid, SIGCONT);
        waitpid(pid, NULL, 0);
        printf("child has died.\n");
    }
    else
    {
        execve(argv[1], &argv[1], envp);
    }
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_int(int signo);
void sig_int2(int signo)
{
    printf("I'm signal 2\n");
    sleep(2);
}

int main()
{
    sigset_t newmask, oldmask, waitmask;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        perror("signal error\n");
        exit(1);
    }

    signal(SIGINT, sig_int2);
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        perror("sigprocmask error\n");
        exit(1);
    }

    printf("in critical region\n");

    if (sigsuspend(&waitmask) != -1)
    {
        perror("sigsuspend error");
        exit(1);
    }

    printf("return from sigsuspend\n");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        perror("reset sigprocmask error\n");
        exit(1);
    }

    return 0;
}

void sig_int(int signo)
{
    printf("sig init\n");
}


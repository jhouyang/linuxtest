#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_int(int signo);

int main()
{
    sigset_t newmask, oldmask, waitmask;

    struct sigaction act, oact;
    act.sa_handler = sig_int;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;
    if (sigaction(SIGINT, &act, &oact) < 0)
    {
        perror("signal error\n");
        exit(1);
    }

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


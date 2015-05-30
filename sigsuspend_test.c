#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile int quitflag;
static void sig_int(int signo)
{
    if (signo == SIGINT)
        printf("interrupted\n");
    else if (signo == SIGQUIT)
        quitflag = 1;
}

int main()
{
    sigset_t zeromask;
    sigemptyset(&zeromask);

    struct sigaction initmask, quitmask, oldact;

    initmask.sa_handler = sig_int;
    initmask.sa_flags = 0;
    sigemptyset(&initmask.sa_mask);

    initmask.sa_handler = sig_int;
    initmask.sa_flags = 0;
    sigemptyset(&initmask.sa_mask);
    if (sigaction(SIGINT, &initmask, &oldact) < 0 ||
            sigaction(SIGQUIT, &quitmask, &oldact) < 0)
    {
        perror("sigint error\n");
        exit(-1);
    }
    printf("begin to sigsuspend\n");

    while (quitflag == 0) {
        printf("check if zero\n");
        // don't block any signal in sigsuspend, and it will:
        // : 1) process signal, such as SIGINT, SIGQUIT
        //   2) call signal function
        //   3) restore signal mask
        //   4) return
        sigsuspend(&zeromask);
    }
    printf("end to sigsuspend\n");
    return 0;
}


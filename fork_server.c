#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m) do { perror(m); exit(EXIT_FAILURE);} while(0)

void do_service(int);

int main(void)
{
    signal(SIGCHLD, SIG_IGN);
    int listenfd;

    if ((listenfd = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP)) < 0)
    {
        ERR_EXIT("socket error");
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    
    int on = 1;

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt error");

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("bind error");

    if (listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen error");

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);

    int conn;

    pid_t pid;

    while (1)
    {
        if ((conn = accept(listenfd, (struct sockaddr*)&servaddr, &peerlen) < 0))
            ERR_EXIT("accept fail");

        pid = fork();

        if (pid == -1)
            ERR_EXIT("fork error");

        if (pid == 0)
        {
            close(listenfd);
            do_service(conn);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(conn);
        }
    }

    return 0;
}

void do_service(int conn)
{
    printf("handle request\n");
    char recvbuff[4096];
    while (1)
    {
        memset(recvbuff, 0, sizeof(recvbuff));
        int ret = 0;
        int nread = 0;
        printf("start to read\n");
        while ((ret = read(conn, recvbuff + nread, sizeof(recvbuff))) > 0)
        {
            nread += ret;
            printf("read aaa\n");
        }

        if (ret == 0)
        {
            // read finished
        }
        else if (errno == EINTR)
            // continue /
            ;
        else
            ERR_EXIT("read error");
    }
}

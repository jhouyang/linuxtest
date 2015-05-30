#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "util.h"

int main()
{
    int connfd;

    if ((connfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0 ) {
        return -1;
    }

    char path[32] = "/tmp/file2";
    struct sockaddr_un addr;
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy((void*)&addr.sun_path, path);
    printf("path %s\n", addr.sun_path);

    if (connect(connfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("connect failed\n");
        printf("errno %d : %s\n", errno, strerror(errno));
        return -1;
    }
    copyData(0, connfd);
    close(connfd);
    printf("close fd");
    return 0;
}

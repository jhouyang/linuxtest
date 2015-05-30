#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    struct sockaddr_un addr;
    int listenfd, connfd;

    if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0 ) {
        printf("socket failed\n");
        return -1;
    }
    char path[32] = "/tmp/file2";
    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    unlink(path);
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy((void*)&addr.sun_path, path);

    if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("bind failed\n");
        printf("error %d\n", errno);
        printf("%s\n", strerror(errno));
        return -1;
    }

    if (listen(listenfd, 5) < 0) {
        return -1;
    }

    printf("listen on fd\n");
    int len = sizeof(addr);
    while ((connfd = accept(listenfd, (struct sockaddr*)&addr, &len)) >= 0) {
        printf("---getting data\n");
        copyData(connfd, 1);
        printf("---done \n");
        close(connfd);
    }
    printf("connfd %d\b", connfd);

    close(listenfd);
    return 0;
}

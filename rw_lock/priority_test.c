#include "my_rw_lock.h"
#include <stdlib.h>

int main()
{
    int fd = open(FILE_PATH, O_RDWR, 0);
    if (fd < 0) {
        perror("open file failed\n");
        return -1;
    }

    if (writew_lock(fd) < 0) {
    //if (readw_lock(fd) < 0) {
        return -1;
    }

    pid_t pid = 0;
    if ((pid = fork()) < 0) {
        perror("fork failed");
        return -1;
    }
    else if (pid == 0){
        sleep(1);
        printf("first child tried to get write lock\n");
        writew_lock(fd);
        printf("first child tried got write lock\n");
        sleep(2);
        unlock(fd);
        exit(0);
    }

    if ((pid = fork()) < 0) {
        perror("fork failed");
        return -1;
    }
    else if (pid == 0){
        sleep(3);
        printf("second child tried to get read lock\n");
        readw_lock(fd);
        printf("second child tried got read lock\n");
        sleep(2);
        unlock(fd);
        exit(0);
    }
    sleep(8);
    unlock(fd);
    printf("parent unlock\n");
 
    return 0;
}

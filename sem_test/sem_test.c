#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("please input sem name\n");
        return -1;
    }
    char* sem_name = argv[1];
    sem_t* id = sem_open(argv[1], O_CREAT | O_EXCL,
            777, 1);
    if (id == SEM_FAILED) {
        perror("sem_open failed:");
        return -1;
    }

    int val = -10;
    if (sem_getvalue(id, &val) < 0) {
        perror("sem_getvalue failed:");
    }
    else {
        printf("current sem_value is %d\n", val);
    }

    if (sem_post(id) < 0) {
        perror("sem_post failed:");
        return -1;
    }

    if (sem_getvalue(id, &val) < 0) {
        perror("sem_getvalue failed:");
    }
    else {
        printf("after post sem_value is %d\n", val);
    }

    if (sem_wait(id) == 0) {
        printf("sem_wait successfully\n");
    }
    else {
        perror("sem_wait failed:");
        return -1;
    }

    if (sem_getvalue(id, &val) < 0) {
        perror("sem_getvalue failed:");
    }
    else {
        printf("after wait sem_value is %d\n", val);
    }

    if (sem_trywait(id) == 0) {
        printf("trywait get the sem\n");
    }
    else if (errno == EAGAIN) {
        printf("no enough source\n");
    }
    else {
        perror("sem_trywait failed\n");
    }

    if (sem_close(id) < 0) {
        perror("sem_close failed:");
        return -1;
    }

    if (sem_unlink(sem_name) < 0) {
        perror("sem_unlink failed:");
        return -1;
    }
    return 0;
}


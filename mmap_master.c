#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
void listen();
 
int main(int argc, char *argv[])
{
    listen();
    return 0;
}
 
void listen()
{
    int fd;
    char *buf;
    char *fname = "/tmp/shm_command";
 
    char command;
    time_t now;
 
    fd = open(fname, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    buf = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    lseek(fd, 4096-1, SEEK_SET);
    int result = write(fd, " ", 1);
    if (close(fd) == -1)
    {
        perror("close");
        exit(1);
    }
    *buf = '0';
    sleep(2);
    for (;;)
    {
        if (*buf == '1' || *buf == '3' || *buf == '5' || *buf == '7')
        {
            if (*buf > '1')
                printf("%ld\tgood job [%c]\n", (long)time(&now), *buf);
            (*buf)++;
        }
        if (*buf == '9')
        {
            break;
        }
        sleep(1);
    }
 
    if (munmap(buf, 4096) == -1)
    {
        perror("munmap");
        exit(1);
    }
 
}

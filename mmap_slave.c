#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
void ready(unsigned int t);
void job_hello();
void job_smile();
void job_bye();
char get_command(char *buf);
void Wait();
 
int main(int argc, char *argv[])
{
    Wait();
    return 0;
}
 
void ready(unsigned int t)
{
    sleep(t);
}
 
/* command 2 */
void job_hello()
{
    time_t now;
    printf("%ld\thello world\n", (long)time(&now));
}
 
/* command 4 */
void job_simle()
{
    time_t now;
    printf("%ld\t^_^\n", (long)time(&now));
}
 
/* command 6 */
void job_bye()
{
    time_t now;
    printf("%ld\t|<--\n", (long)time(&now));
}
 
char get_command(char *buf)
{
    char *p;
    if (buf != NULL)
    {
        p = buf;
    }
    else
    {
        return '0';
    }
    return *p;
}
 
void Wait()
{
    int fd;
    char *buf;
    char *fname = "/tmp/shm_command";
 
    char command;
    time_t now;
 
    fd = open(fname, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    lseek(fd, 4096 - 1, SEEK_SET);
    write(fd, " ", 1);
    buf = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    if (close(fd) == -1)
    {
        perror("close");
        exit(1);
    }
 
    for (;;)
    {
        command = get_command(buf);
        /*printf("%c\n", command);*/
        switch(command)
        {
            case '0':
                printf("%ld\tslave is ready...\n", (long)time(&now));
                ready(3);
                *buf = '1';
                break;
            case '2':
                job_hello();
                *buf = '3';
                break;
            case '4':
                job_simle();
                *buf = '5';
                break;
            case '6':
                job_bye();
                *buf = '7';
                break;
            default:
                break;
        }
        if (*buf == '8')
        {
            *buf = '9';
            if (munmap(buf, 4096) == -1)
            {
                perror("munmap");
                exit(1);
            }
            return;
        }
        sleep(1);
    }
    if (munmap(buf, 4096) == -1)
    {
        perror("munmap");
        exit(1);
    }
}

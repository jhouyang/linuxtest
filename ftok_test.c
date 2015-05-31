#include <sys/ipc.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
    int i = 0;
    for (; i < 10; ++i)
    {
        key_t key = ftok("/home/jouyang", i);
        if (key == -1) {
            perror("invalid key");
        }
        printf("key %x\n", key);
    }
    return 0;
}

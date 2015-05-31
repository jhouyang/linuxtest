#include "my_rw_lock.h"

int main()
{
    int fd = open(FILE_PATH, O_RDWR, 0);
    if (fd < 0) {
        perror("open failed");
    }

    writew_lock(fd);
    printf("process 2 get write lock...\n");
    unlock(fd);

    return 0;
}

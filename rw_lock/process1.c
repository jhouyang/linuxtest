#include "my_rw_lock.h"

int main()
{
    int fd = open(FILE_PATH, O_RDWR, 0);
    if (fd < 0) {
        perror("open failed\n");
    }
 
    writew_lock(fd);
    printf("process 1 get write lock...\n");
    
    sleep(10);
    printf("testlock %d\n", test_write_lock(fd));

    printf("process 1 exit...\n");
    return 0;
}

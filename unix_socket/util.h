#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void copyData(int from, int to) {
    char buf[1024];
    int nread;

    while ((nread = read(from, buf, sizeof(buf))) > 0)
    {
        if (write(to, buf, nread) != nread) {
            return;
        }
    }
}
#endif  // UTIL_H

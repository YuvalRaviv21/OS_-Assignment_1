#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define SIZE_20K 20000

int
main(int argc, char *argv[])
{
    printf("Initial memory usage: %d bytes\n", memsize());
    char *ptr = malloc(SIZE_20K);
    printf("Memory usage after allocation: %d bytes\n", memsize());
    free(ptr);
    printf("Memory usage after release: %d bytes\n", memsize());
    exit(0,0);
}

// TODO 2.5
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MASK 10

int
main(int argc, char *argv[])    // TODO 5.8
{
  set_affinity_mask(MASK);
  for(int i = 0; i < 10; i++) {
    printf("PID: %d\n", getpid());
  }
  exit(0,0);
}
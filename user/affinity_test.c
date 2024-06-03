#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MASK 5 // 10 = 1010 and 5 = 101
int
main(int argc, char *argv[])    // TODO 5.8     1010 - 0100
{
  // printf("PID: %d %d %d\n", getpid(),get_affinity_mask(),get_effective_affinity_mask); // TODO Test
  printf("Start of Affinity_test\n");
  set_affinity_mask(MASK);
  for (int i = 0 ; i < 200;i++){
    // printf("PID: %d %d %d\n", getpid(),get_affinity_mask(),get_effective_affinity_mask);  // TODO Test
    printf("PID: %d\n", getpid());
  }
  exit(0,0);
}
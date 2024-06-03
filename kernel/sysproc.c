#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  char path[32];
  uint64 addr1;
  argaddr(1,&addr1);
  argstr(1, path, sizeof(path));
  exit(n,(addr1 == 0)? 0: path);

  // if in user.h change signature of exit and wait
  // int n;
  // char path[32];
  // argint(0, &n);
  // argstr(1, path, sizeof(path));
  // exit(n,path);
  return 0;  // not reached
}

uint64
sys_get_affinity_mask(void)// TODO TEST
{
  return myproc()->affinity_mask;
}
uint64
sys_get_effective_affinity_mask(void)// TODO TEST
{
  return myproc()->effective_affinity_mask;
}
uint64
sys_getpid(void)
{
  return myproc()->pid;
}
uint64
sys_memsize(void)   // TODO 2.1
{
  return myproc()->sz;
}
uint64 
sys_set_affinity_mask(void) {    // TODO 5.5
  int affinity_mask = 0;
  int effective_affinity_mask = 0;
  argint(0, &affinity_mask);
  argint(0, &effective_affinity_mask);
  // printf("\t affinity_mask = %d\n",affinity_mask1
  acquire(&myproc()->lock);
  myproc()->affinity_mask = affinity_mask; // TODO 5.5
  myproc()->effective_affinity_mask = effective_affinity_mask; // TODO 6
  release(&myproc()->lock);
  return myproc()->affinity_mask;
}
uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p, exit_msg_addr;
  argaddr(0, &p);
  argaddr(1, &exit_msg_addr);
  return wait(p, exit_msg_addr);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

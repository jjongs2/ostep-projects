#include "types.h"
#include "pstat.h"
#include "user.h"

#define NUM_CHILDREN 3
#define NUM_ITERATIONS 25
#define SLEEP_TICKS 100

static int
create_child(int tickets)
{
  int pid;

  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }
  if(pid == 0){
    settickets(tickets);
    while(1)
      ;
  }
  return pid;
}

static void
print_process_info(struct pstat *ps, int iteration)
{
  int i;

  printf(1, "Iteration %d\n", iteration);
  for(i = 0; i < NPROC; i++)
    if(ps->inuse[i] && ps->pid[i] > 3)
      printf(1, "PID %d | Tickets %d | Ticks %d\n", ps->pid[i], ps->tickets[i], ps->ticks[i]);
  printf(1, "\n");
}

int
main(void)
{
  int tickets[NUM_CHILDREN] = {30, 20, 10};
  int pids[NUM_CHILDREN];
  int i;
  struct pstat ps;

  for(i = 0; i < NUM_CHILDREN; i++)
    pids[i] = create_child(tickets[i]);
  for(i = 1; i <= NUM_ITERATIONS; i++){
    sleep(SLEEP_TICKS);
    if(getpinfo(&ps) < 0){
      printf(1, "getpinfo failed\n");
      break;
    }
    print_process_info(&ps, i);
  }
  for(i = 0; i < NUM_CHILDREN; i++)
    kill(pids[i]);
  for(i = 0; i < NUM_CHILDREN; i++)
    wait();
  printf(1, "scheduler test finished\n");
  exit();
}

#include "types.h"
#include "user.h"
#include "mmu.h"

int
main(void)
{
  char *p;
  int pid;
  
  p = sbrk(PGSIZE);
  if(p == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }

  *p = 'a';
  if(mprotect(p, 1) < 0){
    printf(1, "mprotect failed\n");
    exit();
  }
  printf(1, "*p = '%c'\n", *p);

  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }
  if(pid == 0){
    printf(1, "\nattempt to write to protected page...\n");
    *p = 'b';
    printf(1, "should not get here!\n");
    exit();
  }
  wait();

  if(munprotect(p, 1) < 0){
    printf(1, "munprotect failed\n");
    exit();
  }
  printf(1, "\nattempt to write to unprotected page...\n");
  *p = 'c';
  printf(1, "*p = '%c'\n", *p);

  printf(1, "\nprotect test finished\n");
  exit();
}

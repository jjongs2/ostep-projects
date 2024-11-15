#include "types.h"
#include "defs.h"

int
sys_mprotect(void)
{
  void *addr;
  int len;

  if(argptr(0, (void*)&addr, sizeof(addr)) < 0 || argint(1, &len) < 0)
    return -1;
  return mprotect(addr, len);
}

int
sys_munprotect(void)
{
  void *addr;
  int len;

  if(argptr(0, (void*)&addr, sizeof(addr)) < 0 || argint(1, &len) < 0)
    return -1;
  return munprotect(addr, len);
}

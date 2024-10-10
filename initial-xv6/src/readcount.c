#include "types.h"
#include "defs.h"
#include "spinlock.h"

int readcount;
struct spinlock readcountlock;

void
readcountinit(void)
{
  initlock(&readcountlock, "readcount");
}

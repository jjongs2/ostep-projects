#include "types.h"
#include "user.h"

int
main(void)
{
  uchar *p = 0x0;

  printf(1, "attmept to dereference a null pointer...\n");
  printf(1, "0x%x\n", *p);
  printf(1, "should not get here!\n");
  exit();
}

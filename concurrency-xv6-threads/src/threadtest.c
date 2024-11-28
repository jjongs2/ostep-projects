#include "types.h"
#include "user.h"

#define NUM_ITERATIONS 1000
#define NUM_THREADS 4

static int count = 0;
static lock_t count_lock;

void
count_routine(void *arg1, void *arg2)
{
  int i;
  int tid = *(int*)arg1;
  int iters = *(int*)arg2;

  printf(1, "thread %d running...\n", tid);
  for(i = 0; i < iters; i++){
    lock_acquire(&count_lock);
    count++;
    lock_release(&count_lock);
  }
  exit();
}

void
malloc_routine(void *arg1, void *arg2)
{
  char *mem;
  int i, size;
  int tid = *(int*)arg1;

  printf(1, "thread %d running...\n", tid);
  size = tid * 1001;
  if((mem = malloc(size)) == 0){
    printf(1, "thread %d: failed to allocate %d bytes\n", tid, size);
    exit();
  }
  memset(mem, tid, size);
  for(i = 0; i < size; i++){
    if(mem[i] != tid){
      printf(1, "thread %d: memory corruption detected at offset %d\n", tid, i);
      break;
    }
  }
  free(mem);
  exit();
}

void
count_test(void)
{
  int i;
  int tids[NUM_THREADS];
  int iters = NUM_ITERATIONS;
  int expected = NUM_ITERATIONS * NUM_THREADS;

  printf(1, "=== Testing shared variable synchronization ===\n");
  lock_init(&count_lock);
  for(i = 0; i < NUM_THREADS; i++){
    tids[i] = i;
    if(thread_create(count_routine, (void*)&tids[i], (void*)&iters) < 0){
      printf(1, "thread_create failed\n");
      exit();
    }
  }
  for(i = 0; i < NUM_THREADS; i++){
    if(thread_join() < 0){
      printf(1, "thread_join failed\n");
      exit();
    }
  }
  printf(1, "final count: %d (expected: %d)\n\n", count, expected);
}

void
malloc_test(void)
{
  int i;
  int tids[NUM_THREADS];

  printf(1, "=== Testing malloc synchronization ===\n");
  for(i = 0; i < NUM_THREADS; i++){
    tids[i] = i;
    if(thread_create(malloc_routine, (void*)&tids[i], 0) < 0){
      printf(1, "thread_create failed\n");
      exit();
    }
  }
  for(i = 0; i < NUM_THREADS; i++){
    if(thread_join() < 0){
      printf(1, "thread_join failed\n");
      exit();
    }
  }
  printf(1, "malloc test passed\n\n");
}

int
main(void)
{
  count_test();
  malloc_test();
  printf(1, "thread test finished\n");
  exit();
}

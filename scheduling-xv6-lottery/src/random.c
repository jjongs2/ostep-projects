#include "types.h"

static inline uint
rotl(const uint x, int k)
{
    return (x << k) | (x >> (32 - k));
}

static inline uint
splitmix32(uint *x)
{
  uint z = (*x += 0x9e3779b9);

  z = (z ^ (z >> 16)) * 0x85ebca6b;
  z = (z ^ (z >> 13)) * 0xc2b2ae35;
  return z ^ (z >> 16);
}

static uint s[4];

uint
random(void)
{
  const uint result = rotl(s[0] + s[3], 7) + s[0];

  const uint t = s[1] << 9;

  s[2] ^= s[0];
  s[3] ^= s[1];
  s[1] ^= s[2];
  s[0] ^= s[3];

  s[2] ^= t;

  s[3] = rotl(s[3], 11);

  return result;
}

void
seedrandom(uint seed)
{
  int i;

  for(i = 0; i < 4; i++)
    s[i] = splitmix32(&seed);
}

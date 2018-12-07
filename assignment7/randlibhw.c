#include <immintrin.h>
#include "randlib.h"

/* Return a random value, using hardware operations.  */
extern unsigned long long rand64 (void) {
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

extern void
hardware_rand64_init (void)
{
}

/* Return a random value, using hardware operations.  */
extern unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

/* Finalize the hardware rand64 implementation.  */
extern void
hardware_rand64_fini (void)
{
}
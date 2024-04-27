#include <stdio.h>
#include <nox/freeze.h>

void freeze()
{
  for (;;)
  {
    asm("nop"); // we have this so that -O2 doesn't remove the loop
  }
}

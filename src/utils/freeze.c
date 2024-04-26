#include <stdio.h>
#include <utils/freeze.h>

void freeze() {
  for (;;) {
    asm("nop"); // we have this so that -O2 doesn't remove the loop
  }
}

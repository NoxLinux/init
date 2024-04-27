#include <nox/freeze.h>
#include <stdio.h>

void freeze() {
  for (;;) {
    asm("nop"); // we have this so that -O2 doesn't remove the loop
  }
}

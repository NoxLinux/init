#include <stdio.h>
#include <utils/freeze.h>

inline void freeze() {
  for (;;) {
    asm("nop"); // we have this so that -O2 doesn't remove the loop
  }
}

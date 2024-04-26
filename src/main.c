#include <stdio.h>
#include <unistd.h>

int main(void) {
  printf("hello world!\n");

  char buffer[1024];
  for (;;) {
    read(0, buffer, 1024);
  }

  return 0;
}

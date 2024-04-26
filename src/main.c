#include <stdio.h>
#include <unistd.h>
#include <utils/freeze.h>

int main(void) {
  printf("Welcome to \033[1;34mNox\033[0m!\n");

  if (access("/bin/sh", F_OK) == -1) {
    perror("/bin/sh not found, please install a shell!\n");
    freeze();
  }

  for (;;) {
    printf("Starting /bin/sh\n");

    char *const argv[] = {"/bin/sh"};
    execvp("/bin/sh", argv);
  }
}

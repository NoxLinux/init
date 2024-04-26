#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils/freeze.h>
#include <utils/sysprep.h>

int main(void) {
  if (getpgid(1) >= 0 && getpid() != 1) {
    return 1;
  }

  printf("Welcome to \033[1;34mNox\033[0m!\n");

  printf("\n--- Stage 1 ---\n");
  sysprep();

  printf("\n--- Stage 2 ---\n");
  if (access("/bin/sh", F_OK) == -1) {
    perror("!!! /bin/sh not found, please install a shell!\n");
    freeze();
  }

  printf("... Starting /bin/sh\n");
  execl("/bin/sh", "/bin/sh", NULL);
}

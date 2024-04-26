#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils/freeze.h>

int main(void) {
  printf("Welcome to \033[1;34mNox\033[0m!\n");

  if (access("/bin/sh", F_OK) == -1) {
    perror("/bin/sh not found, please install a shell!\n");
    freeze();
  }

  printf("Starting /bin/sh\n");
  execl("/bin/sh", "/bin/sh", NULL);
}

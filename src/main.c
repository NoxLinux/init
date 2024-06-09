#include <nox/logger.h>
#include <nox/sysprep.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
  if (getpgid(1) >= 0 && getpid() != 1)
  {
    return 1;
  }

  printf("Welcome to \033[1;34mNox\033[0m!\n");

  printf("\n--- Stage 1 ---\n");
  sysprep();

  printf("\n--- Stage 2 ---\n");
  if (access("/bin/ash", F_OK) == -1)
    log_fatal("/bin/ash not found, please install a shell!");

  printf("Starting /bin/ash");
  execl("/bin/ash", "/bin/ash", NULL);
}

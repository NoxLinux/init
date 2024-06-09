#include <nox/logger.h>
#include <nox/sysprep.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  if (getpgid(1) >= 0 && getpid() != 1) {
    return 1;
  }

  log_info("Welcome to \033[1;34mNox\033[0m!\n");

  log_info("\n--- Stage 1 ---\n");
  sysprep();

  log_info("\n--- Stage 2 ---\n");
  if (access("/bin/ash", F_OK) == -1)
    log_fatal("/bin/ash not found, please install a shell!");

  log_info("Starting /bin/ash");
  execl("/bin/ash", "/bin/ash", NULL);
}

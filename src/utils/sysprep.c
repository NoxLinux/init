#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utils/freeze.h>
#include <utils/read_cmdline.h>
#include <utils/sysprep.h>

void sysprep() {
  int mkdirerror = 0;

  printf("... Mounting /proc\n");

  mkdirerror = mkdir("/proc", 0555);
  if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST)) {
    perror("!!! Failed to create '/proc'");
    freeze();
  }

  if (mount("proc", "/proc", "proc", 0, NULL) != 0) {
    perror("!!! Failed to mount '/proc'");
    freeze();
  }

  printf("... Mounting /sys\n");

  mkdirerror = mkdir("/sys", 0555);
  if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST)) {
    perror("!!! Failed to create '/sys'");
    freeze();
  }

  if (mount("sys", "/sys", "sysfs", 0, NULL) != 0) {
    perror("!!! Failed to mount '/sys'");
    freeze();
  }

  printf("... Mounting /tmp\n");

  mkdirerror = mkdir("/tmp", 0777);
  if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST)) {
    perror("!!! Failed to create '/tmp'");
    freeze();
  }

  if (mount("tmp", "/tmp", "tmpfs", 0, NULL) != 0) {
    perror("!!! Failed to mount '/tmp'");
    freeze();
  }

  printf("... Mounting /run\n");

  mkdirerror = mkdir("/run", 0555);
  if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST)) {
    perror("!!! Failed to create '/run'");
    freeze();
  }

  if (mount("tmp", "/run", "tmpfs", 0, NULL) != 0) {
    perror("!!! Failed to mount '/run'");
    freeze();
  }

  printf("... Reading kernel cmdline\n");
  char *cmdline = read_cmdline();
  if (cmdline == NULL)
    return;

  char *root_substr = strstr(cmdline, "root=");
  if (root_substr == NULL) {
    free(cmdline);
    return;
  }

  size_t root_index = root_substr - cmdline + strlen("root=");
  if (cmdline[root_index] == 0 || cmdline[root_index] == ' ') {
    free(cmdline);
    return;
  }

  char *root_disk = NULL;

  int root_disk_len = 0;
  for (size_t i = root_index; i < strlen(cmdline); i++)
    if (cmdline[i] != 0 && cmdline[root_index] != ' ') {
      root_disk_len++;
      root_disk = realloc(root_disk, root_disk_len * sizeof(char));

      if (root_disk == NULL) {
        perror("!!! Failed to allocate memory");
        freeze();
      }

      root_disk[root_disk_len - 1] = cmdline[i];
    }

  printf("root=%s\n", root_disk);
  free(cmdline);
  free(root_disk);
}

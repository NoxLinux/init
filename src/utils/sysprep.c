#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utils/freeze.h>
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
}

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utils/ezmount.h>
#include <utils/freeze.h>
#include <utils/read_cmdline.h>
#include <utils/sysprep.h>

void sysprep() {
  printf("... Mounting /proc\n");
  ezmount("proc", "/proc", "proc");

  printf("... Mounting /sys\n");
  ezmount("sys", "/sys", "sysfs");

  printf("... Mounting /tmp\n");
  ezmount("tmp", "/tmp", "tmpfs");

  printf("... Mounting /run\n");
  ezmount("tmp", "/run", "tmpfs");

  printf("... Reading kernel cmdline\n");
  printf("root=%s\n", read_cmdline_arg("root"));
}

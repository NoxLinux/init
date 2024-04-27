#include <nox/ezmount.h>
#include <nox/logger.h>
#include <nox/read_cmdline.h>
#include <nox/sysprep.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void sysprep() {
  log_info("Mounting /proc");
  ezmount("proc", "/proc", "proc", true);

  log_info("Mounting /sys");
  ezmount("sys", "/sys", "sysfs", true);

  log_info("Mounting /tmp");
  ezmount("tmp", "/tmp", "tmpfs", true);

  log_info("Mounting /run");
  ezmount("tmp", "/run", "tmpfs", true);
}

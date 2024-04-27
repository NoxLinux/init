#include <stdbool.h>
#include <utils/ezmount.h>
#include <utils/logger.h>
#include <utils/read_cmdline.h>
#include <utils/sysprep.h>

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

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <utils/ezmount.h>
#include <utils/logger.h>

void ezmount(char *special_file, char *mountpoint, char *fs_type,
             bool is_critical) {
  int mkdirerror = mkdir(mountpoint, 0555);
  if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST)) {
    char error[strlen("Failed to create ''") + strlen(mountpoint) +
               5]; // 5, just in case
    snprintf(error, sizeof(error), "Failed to create '%s'", mountpoint);

    if (is_critical > 0) {
      log_fatal(error);
    }
  }

  if (mount(special_file, mountpoint, fs_type, 0, NULL) != 0) {
    char error[strlen("Failed to mount ''") + strlen(mountpoint) +
               5]; // again, just in case
    snprintf(error, sizeof(error), "Failed to mount '%s'", mountpoint);

    if (is_critical > 0) {
      log_fatal(error);
    }
  }
}

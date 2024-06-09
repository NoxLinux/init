#include <errno.h>
#include <nox/ezmount.h>
#include <nox/logger.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>

void ez_mount(char *special_file, char *mountpoint, char *fs_type,
              bool is_critical) {
  int mkdirerror = mkdir(mountpoint, 0555);
  if (mkdirerror != 0 && errno != EEXIST) {
    char error[strlen("Failed to create ''") + strlen(mountpoint) +
               5]; // 5, just in case
    snprintf(error, sizeof(error), "Failed to create '%s'", mountpoint);

    if (is_critical > 0) {
      log_fatal_errno(error, errno);
    }
  }

  if (mount(special_file, mountpoint, fs_type, 0, NULL) != 0) {
    char error[strlen("Failed to mount ''") + strlen(mountpoint) +
               5]; // again, just in case
    snprintf(error, sizeof(error), "Failed to mount '%s'", mountpoint);

    if (is_critical > 0) {
      log_fatal_errno(error, errno);
    }
  }
}

bool ez_ismounted(char *mountpoint) {
  FILE *fp = fopen("/proc/mounts", "r");
  char line[256];

  if (fp == NULL) {
    log_fatal_errno("Failed to open '/proc/mounts'", errno);
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    if (strstr(line, mountpoint) != NULL) {
      fclose(fp);
      return true;
    }
  }

  fclose(fp);
  return false;
}

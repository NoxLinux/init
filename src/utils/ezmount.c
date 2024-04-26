#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <utils/ezmount.h>
#include <utils/freeze.h>

void ezmount(char *special_file, char *mountpoint, char *fs_type) {
  int mkdirerror = mkdir(mountpoint, 0555);
  if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST)) {
    char error[strlen("!!! Failed to create ''") + strlen(mountpoint)];
    snprintf(error, sizeof(error), "!!! Failed to create '%s'", mountpoint);
    perror(error);
    freeze();
  }

  if (mount(special_file, mountpoint, fs_type, 0, NULL) != 0) {
    char error[strlen("!!! Failed to mount ''") + strlen(mountpoint)];
    snprintf(error, sizeof(error), "!!! Failed to mount '%s'", mountpoint);
    perror(error);
    freeze();
  }
}

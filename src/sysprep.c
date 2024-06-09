#include <errno.h>
#include <nox/ezmount.h>
#include <nox/freeze.h>
#include <nox/logger.h>
#include <nox/read_cmdline.h>
#include <nox/sysprep.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void sysprep() {
  log_info("Mounting /proc");
  ez_mount("proc", "/proc", "proc", true);

  log_info("Mounting /sys");
  ez_mount("sys", "/sys", "sysfs", true);

  log_info("Mounting /tmp");
  ez_mount("tmp", "/tmp", "tmpfs", true);

  log_info("Mounting /run");
  ez_mount("tmp", "/run", "tmpfs", true);

  log_info("Reading kernel cmdline");
  char *root_fs = read_cmdline_arg("root");
  if (root_fs == NULL)
    return;

  while (true) {
    if (access("/new_root", F_OK) != -1 && ez_ismounted("new_root")) {
      log_info("/new_root was already mounted, continuing");
      break;
    }

    int mkdirerror = mkdir("/new_root", 0555);
    if (mkdirerror != 0 && (mkdirerror != -1 || mkdirerror != EEXIST))
      log_fatal_errno("Failed to mkdir /new_root", errno);

    if (strlen(root_fs) > 5 && strncmp(root_fs, "UUID=", 5) == 0) {
      char root_fs_uuid[strlen(root_fs)];

      for (size_t i = 0; i < strlen(root_fs); i++)
        root_fs_uuid[i] = 0; // initialize with null term just in case
      for (size_t i = 0; i < strlen(root_fs) - 5; i++)
        root_fs_uuid[i] = root_fs[i + 5];

      char root_fs_uuid_path[strlen(root_fs_uuid) +
                             strlen("/dev/disk/by-uuid/")];
      snprintf(root_fs_uuid_path, sizeof(root_fs_uuid_path),
               "/dev/disk/by-uuid/%s", root_fs_uuid);
      char waiting_log_msg[strlen(root_fs_uuid_path) + strlen("Waiting for ")];
      snprintf(waiting_log_msg, sizeof(waiting_log_msg), "Waiting for %s",
               root_fs_uuid_path);

      for (int i = 0; i < 5; i++) {
        if (access(root_fs_uuid_path, F_OK) != -1)
          break;
        log_warn(waiting_log_msg);
        sleep(2);
      }

      if (access(root_fs_uuid_path, F_OK) == -1) {
        if (access("/bin/ash", F_OK) == -1)
          log_fatal("Can't mount root, no emergency shell found.");

        log_err("Can't mount root, you are now in emergency mode.");
        system("/bin/ash");
        log_info("Reloading init (this probably won't work)");
        continue;
      }

      log_info("Mounting /new_root");
      ez_mount(root_fs_uuid_path, "/new_root", "auto", true);
    }
  }
}

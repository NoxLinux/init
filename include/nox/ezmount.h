#ifndef EZMOUNT_H
#define EZMOUNT_H
#include <stdbool.h>

void ez_mount(char *special_file, char *mountpoint, char *fs_type,
              bool is_critical);
bool ez_ismounted(char *mountpoint);

#endif

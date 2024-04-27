#ifndef UTILS_EZMOUNT_H
#define UTILS_EZMOUNT_H
#include <stdbool.h>

void ezmount(char *special_file, char *mountpoint, char *fs_type,
             bool is_critical);

#endif

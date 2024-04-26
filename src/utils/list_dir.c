#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <utils/list_dir.h>

directory_listing list_dir(const char *path) {
  directory_listing result;
  result.num_files = 0;
  result.num_folders = 0;
  result.entries = NULL;

  DIR *dir = opendir(path);
  if (dir == NULL) {
    result.num_files = -1;
    result.num_folders = -1;
    return result;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    result.entries =
        realloc(result.entries, (result.num_files + result.num_folders + 1) *
                                    sizeof(struct dirent *));
    result.entries[result.num_files + result.num_folders] =
        malloc(sizeof(struct dirent));
    memcpy(result.entries[result.num_files + result.num_folders], entry,
           sizeof(struct dirent));

    if (entry->d_type == DT_REG)
      result.num_files++;
    else if (entry->d_type == DT_DIR)
      result.num_folders++;
  }

  closedir(dir);
  return result;
}

#ifndef LIST_DIR_H
#define LIST_DIR_H

typedef struct {
  int num_files;
  int num_folders;
  struct dirent **entries;
} directory_listing;

directory_listing list_dir(const char *path);

#endif

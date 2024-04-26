#include <dirent.h>
#include <stdio.h>
#include <utils/freeze.h>
#include <utils/list_dir.h>

int main(void) {
  printf("hello world!\n");

  directory_listing listing = list_dir("/");

  if (listing.num_files == -1) {
    perror("failed to list /\n");
    freeze();
  }

  printf("dirs: %d\nfiles: %d\n", listing.num_folders, listing.num_files);
  for (int i = 0; i < (listing.num_files + listing.num_folders); i++) {
    if (listing.entries[i]->d_type == DT_REG)
      printf("%s\n", listing.entries[i]->d_name);
    else if (listing.entries[i]->d_type == DT_DIR)
      printf("%s/\n", listing.entries[i]->d_name);
  }

  freeze();
  return 0;
}

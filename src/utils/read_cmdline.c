#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/freeze.h>
#include <utils/read_cmdline.h>

#define CMDLINE_SIZE 2048

char *read_cmdline() {
  char *cmdline = (char *)malloc(CMDLINE_SIZE * sizeof(char));

  if (cmdline == NULL) {
    perror("!!! Failed to allocate memory");
    freeze();
  }

  for (int i = 0; i < CMDLINE_SIZE; i++) {
    cmdline[i] = 0;
  }

  FILE *cmdline_file = fopen("/proc/cmdline", "r");
  if (cmdline_file == NULL) {
    perror("!!! Failed to open '/proc/cmdline'");
    free(cmdline);
    return NULL;
  }

  if (fgets(cmdline, CMDLINE_SIZE, cmdline_file) == NULL) {
    perror("!!! Failed to read '/proc/cmdline'");
    fclose(cmdline_file);
    free(cmdline);
    return NULL;
  }

  fclose(cmdline_file);
  return cmdline;
}

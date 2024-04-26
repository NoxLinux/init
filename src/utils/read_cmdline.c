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

char *read_cmdline_arg(char *argname) {
  char *cmdline = read_cmdline();
  if (cmdline == NULL)
    return NULL;

  char arg_equalsign_str[strlen(argname) + 2];
  snprintf(arg_equalsign_str, sizeof(arg_equalsign_str), "%s=", argname);

  char *root_substr = strstr(cmdline, arg_equalsign_str);
  if (root_substr == NULL) {
    free(cmdline);
    return NULL;
  }

  size_t arg_index = root_substr - cmdline + strlen(arg_equalsign_str);
  if (cmdline[arg_index] == 0 || cmdline[arg_index] == ' ') {
    free(cmdline);
    return NULL;
  }

  char *arg = NULL;

  int arg_len = 0;
  for (size_t i = arg_index; i < strlen(cmdline); i++)
    if (cmdline[i] != 0 && cmdline[arg_index] != ' ') {
      arg_len++;
      arg = realloc(arg, arg_len * sizeof(char));

      if (arg == NULL) {
        perror("!!! Failed to allocate memory");
        freeze();
      }

      arg[arg_len - 1] = cmdline[i];
    }

  free(cmdline);
  return arg;
}

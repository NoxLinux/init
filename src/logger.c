#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <nox/freeze.h>
#include <nox/logger.h>

void log_info(char *msg) { printf("\033[1;34m===\033[0m %s\n", msg); }

void log_warn(char *msg) { fprintf(stderr, "\033[1;33m=!=\033[0m %s\n", msg); }

void log_err(char *msg) { fprintf(stderr, "\033[31m!!!\033[0m %s\n", msg); }

void log_fatal(char *msg)
{
  fprintf(stderr, "\033[1;31m!!!\033[0m %s\n", msg);
  freeze();
}

void log_errno(char *msg, int p_errno)
{
  char error[strlen(msg) + strlen(strerror(p_errno)) +
             10]; // 10, just in case lol
  snprintf(error, sizeof(error), "%s: %s", msg, strerror(errno));
  log_err(error);
}

void log_fatal_errno(char *msg, int p_errno)
{
  char error[strlen(msg) + strlen(strerror(p_errno)) +
             10]; // 10, just in case lol
  snprintf(error, sizeof(error), "%s: %s", msg, strerror(errno));
  log_fatal(error);
}

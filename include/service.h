#ifndef SERVICE_H
#define SERVICE_H
#include <stdbool.h>
#include <sys/types.h>

typedef struct {
  const char *name;
  bool running;
  pid_t pid;
} Service;

#endif

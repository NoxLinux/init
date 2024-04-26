#ifndef SERVICE_H
#define SERVICE_H
#include <stdbool.h>

typedef struct {
  const char *name;
  bool running;
  int pid;
} Service;

#endif

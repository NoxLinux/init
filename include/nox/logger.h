#ifndef LOGGER_H
#define LOGGER_H

void log_info(char *msg);
void log_warn(char *msg);
void log_err(char *msg);
void log_fatal(char *msg);
void log_errno(char *msg, int p_errno);
void log_fatal_errno(char *msg, int p_errno);

#endif

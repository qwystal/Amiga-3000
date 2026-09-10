#ifndef DEBUG_H
#define DEBUG_H

extern size_t internal_error;
extern byte suppress_errors;

void error(const char *msg);
void info(const char *msg);
void success(const char *msg);

#endif
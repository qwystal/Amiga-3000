#include <stdio.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

void error(const char *msg) {
    printf("%serror:%s %s\n", COLOR_RED, COLOR_RESET, msg);
}

void info(const char *msg) {
    printf("info: %s\n", msg);
}
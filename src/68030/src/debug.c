#include <stdio.h>
#include <string.h>
#include "typedefs.h"
#include "debug.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

size_t internal_error = 0;
byte suppress_errors = 0;

void error(const char *msg) {

    if (!suppress_errors)
    {
        printf("%serror:%s %s\n", COLOR_RED, COLOR_RESET, msg);
    }
    
    internal_error++;
}

void info(const char *msg) {
    printf("info: %s\n", msg);
}

void success(const char *msg) {
    printf("%sok:%s %s\n", COLOR_GREEN, COLOR_RESET, msg);
}
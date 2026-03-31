#include <stdio.h>
#include <string.h>
#include "typedefs.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

size_t internal_error = 0;
byte suppress_errors = 0;
size_t error_types[256] = {0};
const char *error_msgs[] = {
    [MEMORY_ACCESS_VIOLATION] = "out of bounds memory access",
    [UNSUPPORTED_SEF] = "unsupported stack exception frame",
    [ASSERT_FAILURE] = "assertion failed"
};

void error(error_type err_type) {
    (*(error_types + (err_type * sizeof(size_t))))++;

    if (!suppress_errors)
    {
        printf("%serror:%s %s\n", COLOR_RED, COLOR_RESET, error_msgs[err_type]);
    }
    
    internal_error++;
}

void info(const char *msg) {
    printf("info: %s\n", msg);
}

void success(const char *msg) {
    printf("%sok:%s %s\n", COLOR_GREEN, COLOR_RESET, msg);
}
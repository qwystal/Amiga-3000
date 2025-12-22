#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#define UNIT_TEST

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

#define ASSERT(x, msg) \
if (x) {\
    success(msg);\
}\
else {\
    error(msg);\
}\



#endif
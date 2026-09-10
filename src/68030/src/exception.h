#ifndef EXCEPTION_C
#define EXCEPTION_C

#include "typedefs.h"

void write_sef(a3000_t *a3000, word format, word vector); // write stack exception frame
void exception(a3000_t *a3000, word vector); // called on exceptions like VEC_ILLEGAL_INSTRUCTION

#endif
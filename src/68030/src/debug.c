#include <stdio.h>

#include "typedefs.h"

void logError(const char *msg, const A3000 a3000) {
    switch (a3000.debugLevel)
    {
        case 0x1:
            printf("Error: %s\n", msg);
            break;
        
        case 0x0:
            break;

        default:
            break;
    }
}

void logInfo(const char *msg, const A3000 a3000) {
    switch (a3000.debugLevel)
    {
        case 0x1:
            printf("Info: %s\n", msg);
            break;
        
        case 0x0:
            break;

        default:
            break;
    }
}

void logSuccess(const char *msg, const A3000 a3000) {
    switch (a3000.debugLevel)
    {
        case 0x1:
            printf("Success: %s\n", msg);
            break;
        
        case 0x0:
            break;

        default:
            break;
    }
}
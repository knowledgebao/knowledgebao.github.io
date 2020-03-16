#ifndef SSN_H
#define SSN_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef SSN_API_BEGIN
#    ifdef __cplusplus
#        define SSN_API_BEGIN extern "C" {
#        define SSN_API_END }
#    else 
#        define SSN_API_BEGIN
#        define SSN_API_END
#    endif
#endif // SSN_API

#ifndef SSN_LOG_DEVICE
#define SSN_LOG_DEVICE stdout
#endif // LOG_DEVICE

#ifndef SSN_LOGF
#define SSN_LOGF(fmt, ...) do{ \
    if(SSN_LOG_DEVICE==NULL) { \
        break;             \
    }                      \
    const char* filename = __FILE__;          \
    const char* pos = strrchr(filename, '/'); \
    if(pos) {             \
        filename = pos+1; \
    }                     \
    fprintf(SSN_LOG_DEVICE, "%s:%d\t", filename, __LINE__); \
    fprintf(SSN_LOG_DEVICE, fmt, ##__VA_ARGS__);            \
    fprintf(SSN_LOG_DEVICE, "\n");                          \
} while(0)
#endif // SSN_LOGF

#endif
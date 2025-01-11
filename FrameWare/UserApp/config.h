#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdint-gcc.h>

typedef enum {
    CONFIG_RESTORE = 0,
    CONFIG_OK,
    CONFIG_COMMIT
} ConfigStatus_t;

typedef struct {
    ConfigStatus_t configStatus;
    uint32_t canNodeId;
} BoardConfig_t;

extern BoardConfig_t boardConfig;

#endif
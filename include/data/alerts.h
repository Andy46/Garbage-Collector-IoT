
#ifndef _INCLUDE_DATA_ALERTS_H_
#define _INCLUDE_DATA_ALERTS_H_

#include <stdbool.h>

// Container status type
typedef struct {
    bool filled;
    bool temperature;
    bool humidity;
    bool position;
} t_alerts;

#endif // _INCLUDE_DATA_ALERTS_H_

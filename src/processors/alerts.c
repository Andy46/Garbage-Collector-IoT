
#ifndef _INCLUDE_PROCESSORS_ALERTS_H_
#define _INCLUDE_PROCESSORS_ALERTS_H_

#include <stdbool.h>
#include "processors/alerts.h"
#include "data/container.h"

bool alertFilled (t_fill filled)
{
    return filled >= F_75P;
}

bool alertTemperature (t_temperature temperature_status)
{
    return temperature_status >= T_HIGH;
}

bool alertHumidity (t_humidity humidity)
{
    return humidity >= H_HIGH;
}

bool alertPosition (t_position position)
{
    return false;
}

#endif // _INCLUDE_PROCESSORS_ALERTS_H_
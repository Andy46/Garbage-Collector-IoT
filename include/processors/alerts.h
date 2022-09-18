
#ifndef _INCLUDE_PROCESSORS_ALERTS_H_
#define _INCLUDE_PROCESSORS_ALERTS_H_

#include <stdbool.h>
#include "data/container.h"

bool alertFilled (t_fill filled);
bool alertTemperature (t_temperature t_temperature);
bool alertHumidity (t_humidity humidity);
bool alertPosition (t_position position);

#endif // _INCLUDE_PROCESSORS_ALERTS_H_
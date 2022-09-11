
#ifndef _INCLUDE_BLUETOOTH_H_
#define _INCLUDE_BLUETOOTH_H_

#include <stdint.h>

#include "container.h"

void bt_init ();

void bt_update (t_container new_data);

#endif // _INCLUDE_BLUETOOTH_H_

#ifndef _INCLUDE_BLUETOOTH_H_
#define _INCLUDE_BLUETOOTH_H_

#include "data/container.h"
#include "data/alerts.h"

void bt_init ();

void bt_update (t_container new_data, t_alerts new_alerts);

#endif // _INCLUDE_BLUETOOTH_H_
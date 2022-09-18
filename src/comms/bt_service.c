
#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

// #include <bluetooth/services/lbs.h>

#include <zephyr/logging/log.h>

#include "comms/bt_service.h"

static struct bt_svc_cb       svc_cb;

static ssize_t svc_data_filled (struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  void *buf,
			  uint16_t len,
			  uint16_t offset)
{
	printk ("svc_data_filled called!\n");

	return 0;
}
static ssize_t svc_data_humidity (struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  void *buf,
			  uint16_t len,
			  uint16_t offset)
{
	printk ("svc_data_humidity called!\n");

	return 0;
}

/* LED Button Service Declaration */
BT_GATT_SERVICE_DEFINE(data_svc,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_SVC_DATA),
	// Filled characteristic 
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_FILLED,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, svc_data_filled, NULL, NULL),
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_HUMIDITY,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, svc_data_humidity, NULL, NULL),
);

int bt_svc_init(struct bt_svc_cb *callbacks)
{
	if (callbacks) {
		svc_cb.data_cb   = callbacks->data_cb;
		svc_cb.alerts_cb = callbacks->alerts_cb;
	}

	return 0;
}

int bt_svc_notify(void)
{
	int i = 2;
	for (int j=0; j < data_svc.attr_count;j++)
	{
		bt_gatt_notify(NULL, &(data_svc.attrs[j]),
						&i, sizeof(int));
	}
	return 0;
}

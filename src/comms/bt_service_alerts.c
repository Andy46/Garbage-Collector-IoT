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

#include <zephyr/logging/log.h>

#include "comms/bt_service_alerts.h"

// Service data 
static t_alerts alerts = {0};

#define TAG_ACTIVE   "ACTIVE" 
#define TAG_INACTIVE "INACTIVE"
/* Bluetooth GATT read functions */

static char* get_tag (bool value)
{
 	if (value) return TAG_ACTIVE;
	else 	   return TAG_INACTIVE;
}

static ssize_t read_alerts_filled(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_alerts_filled called\n");
 	char *value = get_tag (alerts.filled);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

static ssize_t read_alerts_humidity(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_alerts_humidity called\n");
 	char *value = get_tag (alerts.humidity);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

static ssize_t read_alerts_temperature(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_alerts_temperature called\n"); 	
	char *value = get_tag (alerts.temperature);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

static ssize_t read_alerts_position(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_alerts_position called\n"); 	
	char *value = get_tag (alerts.position);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

/* Update function */
void bt_svc_alerts_update (t_alerts new_alerts)
{
    alerts = new_alerts;
}

/* ALERTS Service Declaration */
BT_GATT_SERVICE_DEFINE(alerts_svc,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_SVC_ALERTS),
	// Filled 
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_ALERTS_FILLED,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_alerts_filled, NULL, NULL),
	// Humidity
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_ALERTS_HUMIDITY,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_alerts_humidity, NULL, NULL),
	// Temperature
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_ALERTS_TEMPERATURE,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_alerts_temperature, NULL, NULL),
	// Position
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_ALERTS_POSITION,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_alerts_position, NULL, NULL),
);

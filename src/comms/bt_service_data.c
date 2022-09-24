
#include <zephyr/types.h>
#include <stddef.h>
#include <stdio.h>
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

#include "comms/bt_service_data.h"

// Service data 
static t_container container = {0};

/* Convert values to strings */

#define STR_LEN 20

const char* VALUES_FILL [F_FULL+1] = {
	"ERROR",
	"EMPTY",
	"25P",
	"50P",
	"75P",
	"FULL"
};

const char* VALUES_HUMIDITY [H_HIGH+1] = {
	"ERROR",
	"LOW",
	"MEDIUM",
	"HIGH"
};

const char* VALUES_TEMPERATURE [T_HIGH+1] = {
	"ERROR",
	"LOW",
	"MEDIUM",
	"HIGH"
};

const char* get_filled_str ()
{
	return VALUES_FILL [container.fill];
}

void get_humidity_str (char *str, uint32_t len)
{
	snprintk(str, len, "%s (%d %%)", VALUES_HUMIDITY [container.humidity], (uint32_t) container.humidity_val);
}

void get_temperature_str (char *str, uint32_t len)
{
	snprintk(str, STR_LEN, "%s (%d ºC)", VALUES_HUMIDITY [container.temperature], (uint32_t) container.temperature_val);
}

void get_position_str (char *str, uint32_t len, float val)
{
	snprintk (str, STR_LEN, "%d", (uint32_t) val);
}

/* Bluetooth GATT read functions */

static ssize_t read_data_filled(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_data_filled called\n");
	const char* value = get_filled_str ();
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));
}

static ssize_t read_data_humidity(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_data_humidity called\n");
	char str[STR_LEN];
	get_humidity_str (str, STR_LEN);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, str, strlen(str));
}

static ssize_t read_data_temperature(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_data_temperature called\n");
	char str[STR_LEN];
	get_temperature_str (str, STR_LEN);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, str, strlen(str));
}

static ssize_t read_data_positionX(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_data_positionX called\n");
	char str[STR_LEN];
	get_position_str (str, STR_LEN, container.position.x_axis);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, str, strlen(str));
}

static ssize_t read_data_positionY(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_data_positionY called\n");
	char str[STR_LEN];
	get_position_str (str, STR_LEN, container.position.y_axis);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, str, strlen(str));
}

static ssize_t read_data_positionZ(struct bt_conn *conn, 
								const struct bt_gatt_attr *attr,
   								void *buf, 
								uint16_t len, 
								uint16_t offset)
{
	printk ("read_data_positionZ called\n");
	char str[STR_LEN];
	get_position_str (str, STR_LEN, container.position.z_axis);
 	return bt_gatt_attr_read(conn, attr, buf, len, offset, str, strlen(str));
}

/* Update function */
void bt_svc_data_update (t_container new_data)
{
    container = new_data;
}

/* DATA Service Declaration */
BT_GATT_SERVICE_DEFINE(data_svc,
	BT_GATT_PRIMARY_SERVICE(BT_UUID_SVC_DATA),
	// Filled 
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_FILLED,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_data_filled, NULL, NULL),
	// Humidity
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_HUMIDITY,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_data_humidity, NULL, NULL),
	// Temperature
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_TEMPERATURE,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_data_temperature, NULL, NULL),
	// Position
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_POSITION_X,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_data_positionX, NULL, NULL),
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_POSITION_Y,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_data_positionY, NULL, NULL),
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_DATA_POSITION_Z,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_data_positionZ, NULL, NULL),
);

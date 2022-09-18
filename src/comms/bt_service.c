
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

static bool                   notify_enabled;
static bool                   button_state;
static struct bt_svc_cb       svc_cb;

static void lbslc_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				  uint16_t value)
{
	printk ("lbslc_ccc_cfg_changed called!\n");
	notify_enabled = (value == BT_GATT_CCC_NOTIFY);
}

static ssize_t write_led(struct bt_conn *conn,
			 const struct bt_gatt_attr *attr,
			 const void *buf,
			 uint16_t len, uint16_t offset, uint8_t flags)
{
	printk ("write_led called!\n");
	
	return len;
}

static ssize_t read_button(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  void *buf,
			  uint16_t len,
			  uint16_t offset)
{
	printk ("read_button called!\n");

	return 0;
}

/* LED Button Service Declaration */
BT_GATT_SERVICE_DEFINE(bt_svc,
BT_GATT_PRIMARY_SERVICE(BT_UUID_SVC),
#if 1
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_BUTTON,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_button, NULL,
			       &button_state),
#else
	BT_GATT_CHARACTERISTIC(BT_UUID_LBS_BUTTON,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, NULL, NULL, NULL),
#endif
	BT_GATT_CCC(lbslc_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
	BT_GATT_CHARACTERISTIC(BT_UUID_SVC_LED,
			       BT_GATT_CHRC_WRITE,
			       BT_GATT_PERM_WRITE,
			       NULL, write_led, NULL),
);

int bt_svc_init(struct bt_svc_cb *callbacks)
{
	if (callbacks) {
		svc_cb.service1_cb = callbacks->service1_cb;
		svc_cb.service2_cb = callbacks->service2_cb;
	}

	return 0;
}

// int bt_lbs_send_button_state(bool button_state)
// {
// 	if (!notify_enabled) {
// 		return -EACCES;
// 	}

// 	return bt_gatt_notify(NULL, &lbs_svc.attrs[2],
// 			      &button_state,
// 			      sizeof(button_state));
// }

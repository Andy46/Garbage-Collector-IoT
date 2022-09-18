/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _INCLUDE_BT_SERVICE_H_
#define _INCLUDE_BT_SERVICE_H_

/**@file
 * @defgroup bt_svc LED Button Service API
 * @{
 * @brief API for the LED Button Service (SVC).
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/types.h>

/** @brief SVC Service 1 (DATA) UUID. */
#define BT_UUID_SVC_DATA_VAL \
	BT_UUID_128_ENCODE(0x00010000, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA_FILLED_VAL \
	BT_UUID_128_ENCODE(0x00010001, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA_HUMIDITY_VAL \
	BT_UUID_128_ENCODE(0x00010002, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA_TEMPERATURE_VAL \
	BT_UUID_128_ENCODE(0x00010003, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA_POSITION_X_VAL \
	BT_UUID_128_ENCODE(0x00010004, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA_POSITION_Y_VAL \
	BT_UUID_128_ENCODE(0x00010005, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA_POSITION_Z_VAL \
	BT_UUID_128_ENCODE(0x00010006, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

/** @brief SVC Service 1 (ALERTS) UUID. */
#define BT_UUID_SVC_ALERTS_VAL \
	BT_UUID_128_ENCODE(0x00020000, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_ALERTS_FILLED_VAL \
	BT_UUID_128_ENCODE(0x00020001, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_ALERTS_HUMIDITY_VAL \
	BT_UUID_128_ENCODE(0x00020002, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_ALERTS_TEMPERATURE_VAL \
	BT_UUID_128_ENCODE(0x00020003, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_ALERTS_POSITION_VAL \
	BT_UUID_128_ENCODE(0x00020004, 0xd7fa, 0x42d3, 0xb486, 0x962db285a927)

#define BT_UUID_SVC_DATA      			BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_VAL)
#define BT_UUID_SVC_DATA_FILLED			BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_FILLED_VAL)
#define BT_UUID_SVC_DATA_HUMIDITY		BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_HUMIDITY_VAL)
#define BT_UUID_SVC_DATA_TEMPERATURE	BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_TEMPERATURE_VAL)
#define BT_UUID_SVC_DATA_POSITION_X		BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_POSITION_X_VAL)
#define BT_UUID_SVC_DATA_POSITION_Y		BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_POSITION_Y_VAL)
#define BT_UUID_SVC_DATA_POSITION_Z		BT_UUID_DECLARE_128(BT_UUID_SVC_DATA_POSITION_Z_VAL)

#define BT_UUID_SVC_ALERTS     		BT_UUID_DECLARE_128(BT_UUID_SVC_ALERTS_VAL)
#define BT_UUID_SVC_ALERTS_FILLED     	BT_UUID_DECLARE_128(BT_UUID_SVC_ALERTS_FILLED_VAL)
#define BT_UUID_SVC_ALERTS_HUMIDITY    BT_UUID_DECLARE_128(BT_UUID_SVC_ALERTS_HUMIDITY_VAL)
#define BT_UUID_SVC_ALERTS_TEMPERATURE	BT_UUID_DECLARE_128(BT_UUID_SVC_ALERTS_TEMPERATURE_VAL)
#define BT_UUID_SVC_ALERTS_POSITION    BT_UUID_DECLARE_128(BT_UUID_SVC_ALERTS_POSITION_VAL)

typedef bool (*svc_data_cb_t) (void);
typedef bool (*svc_alerts_cb_t) (void);

/** @brief Callback struct used by the Service. */
struct bt_svc_cb {
	/** Service read callback. */
	svc_data_cb_t 	data_cb;
	svc_alerts_cb_t alerts_cb;
};

/** @brief Initialize the Service.
 *
 * This function registers a GATT service with characteristics: Characteristic1, Characteristic2.
 * Send notifications for the Button Characteristic to let connected peers know
 * when the button state changes.
 *
 * @param[in] callbacks Struct containing pointers to callback functions
 *			used by the service. This pointer can be NULL
 *			if no callback functions are defined.
 *
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int bt_svc_init(struct bt_svc_cb *callbacks);

/** @brief Send the button state.
 *
 * This function sends a binary state, typically the state of a
 * button, to all connected peers.
 *
 * @param[in] button_state The state of the button.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int bt_svc_notify(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _INCLUDE_BT_SERVICE_H_ */

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

/** @brief SVC Service UUID. */
#define BT_UUID_SVC_VAL \
	BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief Button Characteristic UUID. */
#define BT_UUID_SVC_BUTTON_VAL \
	BT_UUID_128_ENCODE(0x00001524, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief LED Characteristic UUID. */
#define BT_UUID_SVC_LED_VAL \
	BT_UUID_128_ENCODE(0x00001525, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

#define BT_UUID_SVC           BT_UUID_DECLARE_128(BT_UUID_SVC_VAL)
#define BT_UUID_SVC_BUTTON    BT_UUID_DECLARE_128(BT_UUID_SVC_BUTTON_VAL)
#define BT_UUID_SVC_LED       BT_UUID_DECLARE_128(BT_UUID_SVC_LED_VAL)

typedef bool (*service1_cb_t)(const bool val);
typedef bool (*service2_cb_t)(void);

/** @brief Callback struct used by the Service. */
struct bt_svc_cb {
	/** Service read callback. */
	service1_cb_t service1_cb;
	service2_cb_t service2_cb;
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
int bt_svc_send_service_state(bool service_state);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _INCLUDE_BT_SERVICE_H_ */

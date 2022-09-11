/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _INCLUDE_SENSORS_BMI270_H_
#define _INCLUDE_SENSORS_BMI270_H_

#include <zephyr/drivers/sensor.h>

/* Measurements ranges for Bosch bmi270 */
#define SENSOR_X_MIN (-45)
#define SENSOR_X_MAX (45)
#define SENSOR_Y_MIN (-45)
#define SENSOR_Y_MAX (45)
#define SENSOR_Z_MIN (-45)
#define SENSOR_Z_MAX (45)

/**
 * @brief Initializes Bosch bmi270.
 *
 * @note Has to be called before other functions are used.
 *
 * @return 0 if success, error code if failure.
 */
int bmi270_init(void);

/**
 * @brief Updates and stores internally data measured by bmi270.
 *
 * @note A single call updates temperature, pressure and humidity values at once.
 *
 * @return 0 if success, error code if failure.
 */
// int bmi270_update_measurements(void);

/**
 * @brief Provides last measured value of X axis.
 *
 * @note Call bmi270_get_x_axis() to update the value.
 *
 * @param x_axis [out] x axis value in radians.
 *
 * @return 0 if success, error code if failure.
 */
// int bmi270_get_x_axis(float *x_axis);

/**
 * @brief Provides last measured value of Y axis.
 *
 * @note Call bmi270_get_y_axis() to update the value.
 *
 * @param y_axis [out] y axis value in radians.
 *
 * @return 0 if success, error code if failure.
 */
// int bmi270_get_y_axis(float *y_axis);

/**
 * @brief Provides last measured value of Z axis.
 *
 * @note Call bmi270_get_z_axis() to update the value.
 *
 * @param z_axis [out] z axis value in radians.
 *
 * @return 0 if success, error code if failure.
 */
// int bmi270_get_z_axis(float *z_axis);

#endif /* _INCLUDE_SENSORS_BMI270_H_ */

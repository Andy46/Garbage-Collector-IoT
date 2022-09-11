/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/logging/log.h>

#include "sensors/bmi270.h"

// /*
//  * Sensor value is represented as having an integer and a fractional part,
//  * and can be obtained using the formula val1 + val2 * 10^(-6).
//  */
// #define SENSOR_VAL2_DIVISOR 1000000

static const struct device *bmi270;

// /*
//  * Sensor value is represented as having an integer and a fractional part,
//  * and can be obtained using the formula val1 + val2 * 10^(-6). Negative
//  * values also adhere to the above formula, but may need special attention.
//  * Here are some examples of the value representation:
//  *
//  *      0.5: val1 =  0, val2 =  500000
//  *     -0.5: val1 =  0, val2 = -500000
//  *     -1.0: val1 = -1, val2 =  0
//  *     -1.5: val1 = -1, val2 = -500000
//  */
// static float convert_sensor_value(struct sensor_value value)
// {
// 	float result = 0.0f;

// 	/* Determine sign */
// 	result = (value.val1 < 0 || value.val2 < 0) ? -1.0f : 1.0f;

// 	/* Use absolute values */
// 	value.val1 = value.val1 < 0 ? -value.val1 : value.val1;
// 	value.val2 = value.val2 < 0 ? -value.val2 : value.val2;

// 	/* Calculate value */
// 	result *= (value.val1 + value.val2 / (float)SENSOR_VAL2_DIVISOR);

// 	return result;
// }

int bmi270_init(void)
{
	int err = 0;

	if (bmi270) {
		printk ("Sensor already initialized");
	} else {
		bmi270 = DEVICE_DT_GET(DT_INST(0, bosch_bmi270));
		if (!bmi270) {
			printk ("Failed to get device");
			err = ENODEV;
		}
	    printk("BMI270 Configured!\n");
	}

	return err;
}

// int bme680_update_measurements(void)
// {
// 	int err = 0;

// 	if (bme680) {
// 		err = sensor_sample_fetch(bme680);
// 	} else {
// 		printk ("Sensor not initialized");
// 		err = ENODEV;
// 	}

// 	return err;
// }

// int bme680_get_temperature(float *temperature)
// {
// 	int err = 0;

// 	if (temperature) {
// 		if (bme680) {
// 			struct sensor_value sensor_temperature;

// 			err = sensor_channel_get(bme680,
// 						 SENSOR_CHAN_AMBIENT_TEMP,
// 						 &sensor_temperature);
// 			if (err) {
// 				printk ("Failed to get sensor channel: %d", err);
// 			} else {
// 				printk ("Sensor    T:%3d.%06d [*C]",
// 					sensor_temperature.val1, sensor_temperature.val2);
// 				*temperature = convert_sensor_value(sensor_temperature);
// 			}
// 		} else {
// 			printk ("Sensor not initialized");
// 			err = ENODEV;
// 		}
// 	} else {
// 		printk ("NULL param");
// 		err = EINVAL;
// 	}

// 	return err;
// }

// int bme680_get_pressure(float *pressure)
// {
// 	int err = 0;

// 	if (pressure) {
// 		if (bme680) {
// 			struct sensor_value sensor_pressure;

// 			err = sensor_channel_get(bme680,
// 						 SENSOR_CHAN_PRESS,
// 						 &sensor_pressure);
// 			if (err) {
// 				printk ("Failed to get sensor channel: %d", err);
// 			} else {
// 				printk ("Sensor    P:%3d.%06d [kPa]",
// 					sensor_pressure.val1, sensor_pressure.val2);
// 				*pressure = convert_sensor_value(sensor_pressure);
// 			}
// 		} else {
// 			printk ("Sensor not initialized");
// 			err = ENODEV;
// 		}
// 	} else {
// 		printk ("NULL param");
// 		err = EINVAL;
// 	}

// 	return err;
// }

// int bme680_get_humidity(float *humidity)
// {
// 	int err = 0;

// 	if (humidity) {
// 		if (bme680) {
// 			struct sensor_value sensor_humidity;

// 			err = sensor_channel_get(bme680,
// 						 SENSOR_CHAN_HUMIDITY,
// 						 &sensor_humidity);
// 			if (err) {
// 				printk ("Failed to get sensor channel: %d", err);
// 			} else {
// 				printk ("Sensor    H:%3d.%06d [%%]",
// 					sensor_humidity.val1, sensor_humidity.val2);
// 				*humidity = convert_sensor_value(sensor_humidity);
// 			}
// 		} else {
// 			printk ("Sensor not initialized");
// 			err = ENODEV;
// 		}
// 	} else {
// 		printk ("NULL param");
// 		err = EINVAL;
// 	}

// 	return err;
// }

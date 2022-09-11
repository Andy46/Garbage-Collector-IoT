/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <stddef.h>
#include <string.h>
#include <errno.h>

#include <soc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/settings/settings.h>


// Peripherals includes
#include "hcsr04.h"
#include "bme680.h"
#include "bluetooth.h"

//
#include "container.h"


t_container update_status (void)
{
	t_container container_status;
	float distance = -1.0;
	float temperature = -1.0;
	float humidity = -1.0;
	int err = 0;

	// Update fill status
	distance = hcsr04_measure ();
	if (distance < FILL_ERROR_THRESHOLD)
	{
		container_status.fill_status = F_ERROR;
	} 
	else if (distance >= FILL_EMPTY_THRESHOLD) 
	{
		container_status.fill_status = F_EMPTY;
	} 
	else if (distance >= FILL_25P_THRESHOLD) 
	{
		container_status.fill_status = F_25P;
	} 
	else if (distance >= FILL_50P_THRESHOLD) 
	{
		container_status.fill_status = F_50P;
	} 
	else if (distance >= FILL_75P_THRESHOLD) 
	{
		container_status.fill_status = F_75P;
	} 
	else if (distance >= FILL_FULL_THRESHOLD)
	{
		container_status.fill_status = F_FULL;
	}

	// Update position
	// TODO: Implement
			
	// Update Temperature and Humidity
	err = bme680_update_measurements ();

	err = bme680_get_temperature (&temperature);
	if (err == 0)
	{
		if (temperature <= MIN_TEMP_THRESHOLD)
		{
			container_status.temperature = T_LOW;
		} 
		else if (temperature >= MAX_TEMP_THRESHOLD) 
		{
			container_status.temperature = T_HIGH;
		} 
		else 
		{
			container_status.temperature = T_NORMAL;
		}
	} else {
		container_status.temperature = T_ERROR;
	}
	
	err = bme680_get_humidity (&humidity);
	if (err == 0)
	{
		if (humidity <= HUM_LOW_THRESHOLD)
		{
			container_status.humidity = H_LOW;
		} 
		else if (humidity >= HUM_HIGH_THRESHOLD) 
		{
			container_status.humidity = H_HIGH;
		} 
		else 
		{
			container_status.humidity = H_MEDIUM;
		}
	} else {
		container_status.humidity = H_ERROR;
	}

	return container_status;
}


void main(void)
{
	printk("Starting Custom App\n");
	int counter = 0;
	t_container container = {0};

	// Configure devices
	hcsr04_init ();
	bme680_init ();
	// bt_init ();

	for (;;) {
		// Wait until next measure time
		k_sleep(K_MSEC(1000));
	
		// Loop counter
		counter++;
		printk ("Counter value is %d\n", counter);
		
		// Refresh data
		container = update_status ();


		// Update bluetooth data
		// bt_update (container);

	}
}

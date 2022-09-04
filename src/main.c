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

void main(void)
{
	printk("Starting Custom App\n");
	int counter = 0;
  
	// Configure devices
	hcsr04_config ();

	for (;;) {
		// Wait until next measure time
		k_sleep(K_MSEC(1000));
	
		// Loop counter
		counter++;
		printk ("Counter value is %d\n", counter);
		
		// Refresh data
		hcsr04_measure ();

		// Update bluetooth data
		get_distance();
	}
}

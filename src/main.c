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
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/printk.h>
#include <zephyr/types.h>
#include <zephyr/settings/settings.h>


#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>


// #if !DT_NODE_EXISTS(DT_NODELABEL(hcsr04))
// #error "whoops"
// #endif

// #define MY_HCSR04 DT_NODELABEL(hcsr04)


#define GPIO_OUT_PIN	4
#define GPIO_INT_PIN	5
#define PORT			"GPIO_0"


void main(void)
{
	printk("Starting Custom App\n");
	int counter = 0;
  
	uint32_t cycles_spent;
	uint32_t nanseconds_spent;
	uint32_t val;
	uint32_t cm;
	uint32_t stop_time;
	uint32_t start_time;
	const struct device *dev = device_get_binding(PORT);
	printk ("Port device name: %s\n", dev->name);
	gpio_pin_configure(dev, GPIO_OUT_PIN, GPIO_OUTPUT);
	printk (" Trigger pin configured...\n");
		k_sleep(K_MSEC(1000));
		k_sleep(K_MSEC(1000));
	gpio_pin_configure(dev, GPIO_INT_PIN, (GPIO_INPUT | GPIO_ACTIVE_HIGH));
	printk (" Echo pin configured...\n");
		k_sleep(K_MSEC(1000));
		k_sleep(K_MSEC(1000));

	printk("Configured\n");

	for (;;) {
		k_sleep(K_MSEC(1000));
	
		counter++;
		printk ("Counter value is %d\n", counter);
		
		// Trigger measure
		gpio_pin_set(dev, GPIO_OUT_PIN, 1);
		k_sleep(K_MSEC(10));
		gpio_pin_set(dev, GPIO_OUT_PIN, 0);

		// Check echo response
		do {
		 	val = gpio_pin_get(dev, GPIO_INT_PIN);
		} while (val == 0);
		start_time = k_cycle_get_32();

		do {
			val = gpio_pin_get(dev, GPIO_INT_PIN);
			stop_time = k_cycle_get_32();      
			cycles_spent = stop_time - start_time;
			if (cycles_spent > 1266720) //260cm for 84MHz (((MAX_RANGE * 58000) / 1000000000) * (CLOCK * 1000000))
			{
				break;
			}
		} while (val == 1);

		nanseconds_spent = k_cyc_to_ns_floor64(cycles_spent);
		printk("%d ms\n", nanseconds_spent);
		cm = nanseconds_spent / 58000;
		printk("%d\n", cm);
	}
}

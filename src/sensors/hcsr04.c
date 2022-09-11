#include "sensors/hcsr04.h"

#include <stddef.h>
#include <string.h>
#include <errno.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

static const struct device *hcsr04_dev;

/* Implementation based on https://www.hackster.io/ric96/zephyr-rtos-and-hc-sr04-ultrasonic-sensor-2df11a */

void hcsr04_init ()
{
	printk("Starting HC-SR04 Peripheral\n");

    // Get Port device for HC-SR04
    hcsr04_dev = device_get_binding(HCSR04_PORT);

    if (hcsr04_dev == NULL)
    {
        printk ("Error binding device: HCSR04_PORT");
    }
    else
    {
        printk ("Port device name: %s\n", hcsr04_dev->name);
    }

    // Configure trigger pin
	printk (" Configuring trigger pin.\n");
	gpio_pin_configure(hcsr04_dev, HCSR04_TRIG_PIN, GPIO_OUTPUT);
	printk (" Trigger pin configured.\n");

    // Configure echo pin
    printk (" Configuring echo pin.\n");
    gpio_pin_configure(hcsr04_dev, HCSR04_ECHO_PIN, (GPIO_INPUT | GPIO_ACTIVE_HIGH));
	printk (" Echo pin configured.\n");

	printk("HCSR04 Configured!\n");
}

float hcsr04_measure ()
{
	uint32_t cycle_start;
	uint32_t cycle_stop;
	uint32_t cycle_diff;
	uint32_t measure_time;
	uint32_t val;

	float distance = -1.0f; // in cm

    if (hcsr04_dev != NULL)
    {
		// Trigger measure
		gpio_pin_set(hcsr04_dev, HCSR04_TRIG_PIN, 1);
		k_sleep(K_MSEC(10));
		gpio_pin_set(hcsr04_dev, HCSR04_TRIG_PIN, 0);

		// Check echo response
		do {
		 	val = gpio_pin_get(hcsr04_dev, HCSR04_ECHO_PIN);
		} while (val == 0);
		cycle_start = k_cycle_get_32();

		do {
			val = gpio_pin_get(hcsr04_dev, HCSR04_ECHO_PIN);
			cycle_stop = k_cycle_get_32();      
			cycle_diff = cycle_stop - cycle_start;
			if (cycle_diff > 1266720) //260cm for 84MHz (((MAX_RANGE * 58000) / 1000000000) * (CLOCK * 1000000))
			{
				break;
			}
		} while (val == 1);
        
		measure_time = k_cyc_to_ns_floor64(cycle_diff);
		distance = measure_time / 58000;
		printk("%d ns\n", measure_time);
		printk("%f cm\n", distance);
    }

	return distance;
}

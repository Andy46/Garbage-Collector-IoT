// Standard includes
#include <stddef.h>
#include <string.h>
#include <errno.h>

// SO and board includes
#include <soc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/settings/settings.h>

// Configuration
#include "config/constants.h"

// Peripherals includes
#include "sensors/bme680.h"
#include "sensors/hcsr04.h"

// Data collected/alerts types
#include "data/container.h"
#include "data/alerts.h"

// Data processor functions
#include "processors/alerts.h"

// Communication functions
#include "comms/bluetooth.h"

// Global data
static t_container g_container = {0};
static t_alerts g_alerts = {0};

/**  
 * Initialize phase function
 */
void initialize (void)
{
// 	// Configure sensor peripherals
	hcsr04_init ();
	bme680_init ();
	
	// Configure comms peripherals
 	bt_init ();
}

/**  
 * Data Collection phase function
 */
void data_collection (void)
{
	// Temp variables
	t_container container;
	uint32_t distance = 0;
	float temperature = -1.0;
	float humidity = -1.0;
	int err = 0;

	// Update fill status
	distance = hcsr04_measure ();
	container.fill_val = distance;
	if (distance < FILL_ERROR_THRESHOLD)
	{
		container.fill = F_ERROR;
	} 
	else if (distance >= FILL_EMPTY_THRESHOLD) 
	{
		container.fill = F_EMPTY;
	} 
	else if (distance >= FILL_25P_THRESHOLD) 
	{
		container.fill = F_25P;
	} 
	else if (distance >= FILL_50P_THRESHOLD) 
	{
		container.fill = F_50P;
	} 
	else if (distance >= FILL_75P_THRESHOLD) 
	{
		container.fill = F_75P;
	} 
	else // if (distance >= FILL_FULL_THRESHOLD)
	{
		container.fill = F_FULL;
	}

	// Update Temperature and Humidity
	err = bme680_update_measurements ();

	err = bme680_get_temperature (&temperature);
	container.temperature_val = temperature;
	if (err == 0)
	{
		if (temperature <= MIN_TEMP_THRESHOLD)
		{
			container.temperature = T_LOW;
		} 
		else if (temperature >= MAX_TEMP_THRESHOLD) 
		{
			container.temperature = T_HIGH;
		} 
		else 
		{
			container.temperature = T_NORMAL;
		}
	} else {
		container.temperature = T_ERROR;
	}
	
	err = bme680_get_humidity (&humidity);
	container.humidity_val = humidity;
	if (err == 0)
	{
		if (humidity <= HUM_LOW_THRESHOLD)
		{
			container.humidity = H_LOW;
		} 
		else if (humidity >= HUM_HIGH_THRESHOLD) 
		{
			container.humidity = H_HIGH;
		} 
		else 
		{
			container.humidity = H_MEDIUM;
		}
	} else {
		container.humidity = H_ERROR;
	}

// 	// Update position
// 	// TODO: Implement SPI Driver
	container.position.x_axis = 0.0;
	container.position.y_axis = 0.0;
	container.position.z_axis = 0.0;
	
	// End collection
	g_container = container;
}

/**  
 * Data Processing phase function
 */
void data_processing (void)
{
	t_alerts alerts_status;
	// Process Filled alert
	alerts_status.filled = alertFilled (g_container.fill);

	// Process Temperature alert
	alerts_status.temperature = alertTemperature (g_container.temperature);
	
	// Process Humidity alert
	alerts_status.humidity = alertHumidity (g_container.humidity);
	
	// Process Position alert
	alerts_status.position = alertPosition (g_container.position);

	// End processing
	g_alerts = alerts_status;
}

/**  
 * Data Publication phase function
 */
void data_publication (void)
{
	bt_update (g_container, g_alerts);
}

/** 
 * Main function
 */
void main(void)
{
	printk("Starting Garbage Collection IoT\n");
	
  	// Initialize phase
	initialize ();

	for (;;) {
		// Wait until next measure time
		k_sleep(K_MSEC(SLEEP_TIME_MS));
	
		// Data Collection 
		data_collection ();

		// Data Processing
		data_processing ();

		// Data publication 
		data_publication ();
	}
}

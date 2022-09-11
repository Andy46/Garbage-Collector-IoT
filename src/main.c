// Standard includes
#include <stddef.h>
#include <string.h>
#include <errno.h>

// SO and board includes
#include <soc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/settings/settings.h>

// // Peripherals includes
// #include "sensors/hcsr04.h"
// #include "sensors/bme680.h"

// // Data collected/warnings types
// #include "data/container.h"
// // #include "data/warnings.h"

// // Global data
// static t_container g_container = {0};
// // static t_warnings g_warnings = {0};

/**  
 * Initialize phase function
 */
void initialize (void)
{
// 	// Configure sensor peripherals
// 	bme680_init ();
// 	hcsr04_init ();
	
// 	// Configure comms peripherals
// 	// bt_init ();
}

/**  
 * Data Collection phase function
 */
void data_collection (void)
{
// 	t_container container_status;
// 	float distance = -1.0;
// 	float temperature = -1.0;
// 	float humidity = -1.0;
// 	int err = 0;

// 	// Update fill status
// 	distance = hcsr04_measure ();
// 	if (distance < FILL_ERROR_THRESHOLD)
// 	{
// 		container_status.fill_status = F_ERROR;
// 	} 
// 	else if (distance >= FILL_EMPTY_THRESHOLD) 
// 	{
// 		container_status.fill_status = F_EMPTY;
// 	} 
// 	else if (distance >= FILL_25P_THRESHOLD) 
// 	{
// 		container_status.fill_status = F_25P;
// 	} 
// 	else if (distance >= FILL_50P_THRESHOLD) 
// 	{
// 		container_status.fill_status = F_50P;
// 	} 
// 	else if (distance >= FILL_75P_THRESHOLD) 
// 	{
// 		container_status.fill_status = F_75P;
// 	} 
// 	else if (distance >= FILL_FULL_THRESHOLD)
// 	{
// 		container_status.fill_status = F_FULL;
// 	}

// 	// Update position
// 	// TODO: Implement
			
// 	// Update Temperature and Humidity
// 	err = bme680_update_measurements ();

// 	err = bme680_get_temperature (&temperature);
// 	if (err == 0)
// 	{
// 		if (temperature <= MIN_TEMP_THRESHOLD)
// 		{
// 			container_status.temperature = T_LOW;
// 		} 
// 		else if (temperature >= MAX_TEMP_THRESHOLD) 
// 		{
// 			container_status.temperature = T_HIGH;
// 		} 
// 		else 
// 		{
// 			container_status.temperature = T_NORMAL;
// 		}
// 	} else {
// 		container_status.temperature = T_ERROR;
// 	}
	
// 	err = bme680_get_humidity (&humidity);
// 	if (err == 0)
// 	{
// 		if (humidity <= HUM_LOW_THRESHOLD)
// 		{
// 			container_status.humidity = H_LOW;
// 		} 
// 		else if (humidity >= HUM_HIGH_THRESHOLD) 
// 		{
// 			container_status.humidity = H_HIGH;
// 		} 
// 		else 
// 		{
// 			container_status.humidity = H_MEDIUM;
// 		}
// 	} else {
// 		container_status.humidity = H_ERROR;
// 	}

// 	// End collection
// 	g_container = container_status;
}

/**  
 * Data Processing phase function
 */
void data_processing (void)
{

}

/**  
 * Data Publication phase function
 */
void data_publication (void)
{
	// Update bluetooth data
	// bt_update (container);
}

void main(void)
{
	printk("Starting Garbage Collection IoT App\n");
	int counter = 0;
	
  	// Initialize phase
	initialize ();

	for (;;) {
		// Wait until next measure time
		k_sleep(K_MSEC(1000));
	
		// Loop counter
		counter++;
		printk ("Counter value is %d\n", counter);
		
		// // Data Collection 
		data_collection ();

		// // Data Processing
		data_processing ();

		// // Data publication 
		data_publication ();
	}
}

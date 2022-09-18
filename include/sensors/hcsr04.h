
#ifndef _INCLUDE_SENSORS_HCSR04_H_
#define _INCLUDE_SENSORS_HCSR04_H_

#include <stdint.h>

#define HCSR04_PORT		"GPIO_0"
#define HCSR04_TRIG_PIN	4
#define HCSR04_ECHO_PIN	5

void hcsr04_init ();

uint32_t hcsr04_measure ();

#endif // _INCLUDE_SENSORS_HCSR04_H_
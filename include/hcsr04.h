
#ifndef _INCLUDE_HCSR04_H_
#define _INCLUDE_HCSR04_H_

#include <stdint.h>

void hcsr04_config ();

void hcsr04_measure ();

uint32_t get_distance ();

#endif // _INCLUDE_HCSR04_H_
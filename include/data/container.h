
#ifndef _INCLUDE_DATA_CONTAINER_H_
#define _INCLUDE_DATA_CONTAINER_H_

#include <stdint.h>

// Filled type 
typedef enum {
    F_ERROR = 0,
    F_EMPTY, 
    F_25P, 
    F_50P, 
    F_75P, 
    F_FULL,
} t_fill;

// Status fill is the distance to the garbage inside the container
// The greater the distance, the less garbage in the container
#define FILL_ERROR_THRESHOLD 0.0f
#define FILL_EMPTY_THRESHOLD 100.0f
#define FILL_25P_THRESHOLD 75.0f
#define FILL_50P_THRESHOLD 50.0f
#define FILL_75P_THRESHOLD 25.0f
#define FILL_FULL_THRESHOLD 0.0f

// Positional type
typedef struct {
    float x_axis;
    float y_axis;
    float z_axis;
} t_position;

// Humidity type
typedef enum {
    H_ERROR = 0,
    H_LOW, 
    H_MEDIUM,
    H_HIGH,
} t_humidity;

#define HUM_LOW_THRESHOLD 25.0f
#define HUM_HIGH_THRESHOLD 75.0f

// Temperature type
typedef enum {
    T_ERROR = 0, 
    T_LOW, 
    T_NORMAL,
    T_HIGH,
} t_temperature;

#define MIN_TEMP_THRESHOLD -10.0f
#define MAX_TEMP_THRESHOLD 50.0f

// Container status type
typedef struct {
    t_fill fill;
    uint32_t fill_val;
    t_humidity humidity;
    float humidity_val;
    t_temperature temperature;
    float temperature_val;
    t_position position;
} t_container;

#endif // _INCLUDE_DATA_CONTAINER_H_

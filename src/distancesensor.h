
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#define MY_SENSOR DT_NODELABEL(distancesensor)

const struct device *sensor_dev = DEVICE_DT_GET (MY_SENSOR);
#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

// Sensor read period in seconds
#define SENSOR_CHECK_PERIOD_SEC 30

// Default thresholds
#define DEFAULT_MOISTURE_MIN 35    // percent
#define DEFAULT_MOISTURE_MAX 60    // percent

// Max watering time in seconds per watering session
#define DEFAULT_WATERING_MAX_SEC 60

// Minimum wait time between watering sessions (seconds)
#define DEFAULT_WATERING_COOLDOWN_SEC 300 // 5 minutes

#endif // CONFIG_H

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL
} system_mode_t;

typedef enum {
    PUMP_OFF = 0,
    PUMP_ON
} pump_state_t;

typedef enum {
    LED_NORMAL = 0,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} led_state_t;

typedef struct {
    float moisture_percent; // 0-100
    float temperature_c;
} sensor_data_t;

typedef struct {
    uint8_t moisture_min; // start watering below this
    uint8_t moisture_max; // stop watering when reach this
    uint32_t watering_max_sec; // cap for each session
    uint32_t sensor_check_period_sec;
    system_mode_t mode;
} system_config_t;

#endif // TYPES_H

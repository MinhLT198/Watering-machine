#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H

#include "types.h"

void watering_init(system_config_t *cfg);
void watering_check_and_run(const sensor_data_t *s);
void watering_manual_pulse(uint32_t seconds);

// For reporting
void watering_set_notifier(void (*fn)(const char *));

#endif // WATERING_LOGIC_H
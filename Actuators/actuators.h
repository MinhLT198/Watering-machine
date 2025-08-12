#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "types.h"

void actuators_init(void);
void turn_pump_on(void);
void turn_pump_off(void);
pump_state_t pump_get_state(void);
void led_set_state(led_state_t s);
led_state_t led_get_state(void);

#endif // ACTUATORS_H
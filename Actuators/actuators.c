#include "actuators.h"
#include <stdio.h>
#include <stdlib.h>

static pump_state_t current_pump = PUMP_OFF;
static led_state_t current_led = LED_NORMAL;

void actuators_init(void){
    current_pump = PUMP_OFF;
    current_led = LED_NORMAL;
    printf("[ACT] Actuators initialized. Pump OFF, LED NORMAL\n");
}

void turn_pump_on(void){
    if(current_pump == PUMP_ON) return;
    current_pump = PUMP_ON;
    printf("[ACT] PUMP: ON\n");
}

void turn_pump_off(void){
    if(current_pump == PUMP_OFF) return;
    current_pump = PUMP_OFF;
    printf("[ACT] PUMP: OFF\n");
}

pump_state_t pump_get_state(void){
    return current_pump;
}

void led_set_state(led_state_t s){
    if(current_led == s) {
        printf("[ACT] LED state no change.\n");
        return;
    }
    current_led = s;
    const char *name = "?";
    switch(s){
        case LED_NORMAL: name = "NORMAL (Green)"; break;
        case LED_WATERING: name = "WATERING (Yellow)"; break;
        case LED_LOW_MOISTURE_ALERT: name = "LOW_MOISTURE (Blinking Red)"; break;
        case LED_ERROR: name = "ERROR (Red)"; break;
    }
    printf("[ACT] LED: %s\n", name);
}

led_state_t led_get_state(void){
    return current_led;
}
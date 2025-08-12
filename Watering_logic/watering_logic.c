#include "watering_logic.h"
#include "actuators.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "config.h"
#include <unistd.h>

static system_config_t *cfg_ptr = NULL;
static time_t last_watering_time = 0;
static time_t watering_start_time = 0;
static bool watering_active = false;
static void (*notifier)(const char *) = NULL;

void watering_set_notifier(void (*fn)(const char *)){
    notifier = fn;
}

static void notifyf(const char *msg){
    if(notifier) notifier(msg);
    else printf("[NOTIF] %s\n", msg);
}

void watering_init(system_config_t *cfg){
    cfg_ptr = cfg;
    last_watering_time = 0;
    watering_active = false;
}

void watering_stop_internal(const char *reason){
    turn_pump_off();
    watering_active = false;
    watering_start_time = 0;
    last_watering_time = time(NULL);
    char buf[128];
    snprintf(buf, sizeof(buf), "Watering stopped: %s", reason);
    notifyf(buf);
}

void watering_start_internal(void){
    turn_pump_on();
    watering_active = true;
    watering_start_time = time(NULL);
    notifyf("Watering started");
}

void watering_check_and_run(const sensor_data_t *s){
    if(!cfg_ptr) return;
    time_t now = time(NULL);

    // If already watering, check stop conditions
    if(watering_active){
        double elapsed = difftime(now, watering_start_time);
        if(s->moisture_percent >= cfg_ptr->moisture_max){
            watering_stop_internal("Reached moisture_max");
            led_set_state(LED_NORMAL);
            return;
        }
        if((uint32_t)elapsed >= cfg_ptr->watering_max_sec){
            watering_stop_internal("Reached max watering time");
            led_set_state(LED_NORMAL);
            return;
        }
        // still watering
        led_set_state(LED_WATERING);
        return;
    }

    // Not watering: decide whether to start
    if(cfg_ptr->mode != MODE_AUTO) return; // only auto starts

    if(s->moisture_percent < cfg_ptr->moisture_min){
        // check cooldown
        if(last_watering_time == 0 || (uint32_t)difftime(now, last_watering_time) >= DEFAULT_WATERING_COOLDOWN_SEC){
            watering_start_internal();
            led_set_state(LED_WATERING);
        } else {
            char buf[128];
            snprintf(buf, sizeof(buf), "Moisture low (%.1f%%) but cooling down", s->moisture_percent);
            notifyf(buf);
            led_set_state(LED_LOW_MOISTURE_ALERT);
        }
    } else {
        // moisture ok
        led_set_state(LED_NORMAL);
    }
}

void watering_manual_pulse(uint32_t seconds){
    turn_pump_on();
    watering_active = true;
    watering_start_time = time(NULL);
    notifyf("Watering started"); 
    usleep(1000000 * seconds); // sleep for seconds 
}
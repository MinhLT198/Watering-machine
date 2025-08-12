#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "sensors.h"
#include "actuators.h"
#include "buttons.h"
#include "watering_logic.h"
#include "notifier.h"

int main(void){
    printf("=== Smart Plant Watering System (SPWS) Simulation ===\n");
    printf("Starting...\n");

    // Initialize modules
    sensors_init();
    actuators_init();

    // Configuration
    system_config_t cfg;
    cfg.moisture_min = DEFAULT_MOISTURE_MIN;
    cfg.moisture_max = DEFAULT_MOISTURE_MAX;
    cfg.watering_max_sec = DEFAULT_WATERING_MAX_SEC;
    cfg.sensor_check_period_sec = SENSOR_CHECK_PERIOD_SEC;
    cfg.mode = MODE_AUTO; // default
    printf("[MODE] AUTO mode enabled by default.\n");

    watering_init(&cfg);
    watering_set_notifier(notifier_send);

    sensor_data_t sdata;

    buttons_simulation_instructions();
    bool quit = false;
    while(1){
        // Note: our button functions consume input; to support both keys, call both   
        char button = button_pressed();       
        switch(button){
            case 'm':
            case 'M':
                printf("[BTN] Toggle mode pressed.\n");
                // toggle mode
                cfg.mode = (cfg.mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
                char buf[128];
                snprintf(buf, sizeof(buf), "Mode changed to: %s", cfg.mode==MODE_AUTO?"AUTO":"MANUAL");
                notifier_send(buf);
                if(cfg.mode==MODE_MANUAL){
                    // ensure pump off when switching to manual
                    turn_pump_off();
                }
                break;
            case 'w':
            case 'W':
                printf("[BTN] Manual watering requested.\n");
                sensors_read(&sdata);
                if(cfg.mode == MODE_MANUAL){
                    int sec;
                    printf("[BTN] Enter manual watering duration (seconds): ");
                    scanf("%d", &sec);
                    getchar();
                    printf("[SYS] Waiting for %d seconds...\n", sec);
                    watering_manual_pulse(sec);
                    watering_check_and_run(&sdata);               
                } else {
                    notifier_send("Manual water pressed but system is not in MANUAL mode");
                }
                break;
            case 'q':
            case 'Q':
                quit = true;
                printf("[SYS] Quit command received. Exiting...\n");
                break;
            case 't':
            case 'T':
                break; // continue to next loop iteration
            default:
                printf("[BTN] Unknown command: '%c'. Ignoring.\n", button);
                continue;
        }
        if(quit) break;
        // If in MANUAL mode, skip sensor checks and watering logic
        if(cfg.mode == MODE_MANUAL){
            printf("[SYS] In MANUAL mode, skipping sensor checks and watering logic.\n");
            usleep(200000); // 200 ms sleep to avoid busy-looping
            continue;
        }
        
        // check sensors and watering logic mode auto
        if(cfg.mode == MODE_AUTO){
            printf("[SYS] In AUTO mode, checking sensors and watering logic...\n");
            sensors_read(&sdata);
            char buf[128];
            snprintf(buf, sizeof(buf), "Sensor read -> Moisture: %.1f%%, Temp: %.1fC", sdata.moisture_percent, sdata.temperature_c);
            notifier_send(buf);
            watering_check_and_run(&sdata);
        }

        // Periodic status report
        char buf[128];
        snprintf(buf, sizeof(buf), "STATUS: Mode=%s, Pump=%s, Moisture=%.1f%%, LED=%d",
                    cfg.mode==MODE_AUTO?"AUTO":"MANUAL",
                    pump_get_state()==PUMP_ON?"ON":"OFF",
                    sdata.moisture_percent,
                    led_get_state());
        notifier_send(buf);
        

        // Small sleep to avoid busy-looping
        usleep(200000); // 200 ms
    }
    return 0;
}
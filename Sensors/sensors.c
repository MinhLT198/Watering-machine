#include "sensors.h"
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

static sensor_data_t sensors_data;

void sensors_init(void){
    // Initialize sensors, if needed
    printf("[SENS] Sensors initialized.\n");
    sensors_data.moisture_percent = 50.0f;
    sensors_data.temperature_c = 30.0f;
}


void sensors_read(sensor_data_t *out){
    printf("[SENS] Reading sensors...  [MOISTURE] [TEMPERATURE]\n");
    scanf("%f %f", &sensors_data.moisture_percent, &sensors_data.temperature_c);
    getchar();
    out->moisture_percent = sensors_data.moisture_percent;
    out->temperature_c = sensors_data.temperature_c;
}
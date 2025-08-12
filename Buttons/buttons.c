#include "buttons.h"
#include <stdio.h>
#include <stdlib.h>

// We'll use non-blocking stdin read to simulate buttons.
// Key 'm' toggles mode. Key 'w' triggers manual watering. 'q' to quit.

void buttons_init(void){}

char button_pressed(void){
    printf("Wait press button ...\n");
    char c;
    scanf("%c", &c);
    getchar();
    return c;
}

void buttons_simulation_instructions(void){
    printf("[BTN] Simulation keys: 'm' = toggle MODE_AUTO/MODE_MANUAL, 'w' = manual water (in MANUAL). 't' = continue. 'q' = quit\n");
}

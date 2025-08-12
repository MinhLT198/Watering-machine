#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>

void buttons_init(void);
// Polling: call frequently; returns true if toggled
char button_pressed(void);

// Helper: in simulation, feed input
void buttons_simulation_instructions(void);

#endif // BUTTONS_H

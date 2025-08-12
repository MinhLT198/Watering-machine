#include "notifier.h"
#include <stdio.h>

void notifier_init(void){}

void notifier_send(const char *msg){
    // Simulate by printing
    printf("[NOTIFY] %s\n", msg);
}
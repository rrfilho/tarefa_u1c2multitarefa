#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/osal.h"
#include "tasks/core_task.h"
#include "tasks/semaphore_task.h"
#include "tasks/pedestrian_semaphore_task.h"
#include "tasks/buzzer_task.h"
#include "tasks/display_task.h"

void init() {
    stdio_init_all();
}

int main() {
    init();
    os_create_task(core_task, "Core Task");
    os_create_task(semaphore_task, "Semaphore Task");
    os_create_task(pedestrian_semaphore_task, "Pedestrian Semaphore Task");
    os_create_task(buzzer_task, "Buzzer Task");
    os_create_task(display_task, "Display Task");
    os_start();
}

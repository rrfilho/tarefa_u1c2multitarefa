#include "pedestrian_semaphore_task.h"
#include <stdbool.h>
#include "osal.h"
#include "state.h"
#include "leds.h"

static void normal_pedestrian_semaphore() {
    switch (get_state()) {
        case GREEN: leds_set_red(true); break;
        case RED: leds_set_green(true); break;
    }
    os_sleep_ms(1000);
}

static void nightly_pedestrian_semaphore() {
    leds_set_yellow(true);
    os_sleep_ms(500);
    leds_set_yellow(false);
    os_sleep_ms(500);
}

void pedestrian_semaphore_task() {
    leds_init();
    while (true) {
        leds_clear();
        if (is_nightly_mode()) nightly_pedestrian_semaphore();
        else normal_pedestrian_semaphore();
    }
}
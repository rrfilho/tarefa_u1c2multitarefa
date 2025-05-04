#include "semaphore_task.h"
#include <stdbool.h>
#include "osal.h"
#include "state.h"
#include "led_matrix.h"

static void normal_semaphore() {
    switch (get_state()) {
        case GREEN: led_matrix_set_green(true); break;
        case YELLOW: led_matrix_set_yellow(true); break;
        case RED: led_matrix_set_red(true); break;
    }
    os_sleep_ms(1000);
}

static void nightly_semaphore() {
    led_matrix_set_yellow(true);
    os_sleep_ms(500);
    led_matrix_set_yellow(false);
    os_sleep_ms(500);
}

void semaphore_task() {
    led_matrix_init();
    while (true) {
        if (is_nightly_mode()) nightly_semaphore();
        else normal_semaphore();
    }
}
#include "core_task.h"
#include <stdbool.h>
#include "pico/stdlib.h"
#include "osal.h"
#include "state.h"
#include "buttons.h"

#define GREEN_DURATION_US 10000000 // 10 segundos
#define YELLOW_DURATION_US 3000000 // 3 segundos
#define RED_DURATION_US 10000000   // 10 segundos

#define ATTENTION "Atencao!"
#define CROSS "Atravesse!"
#define WAIT "Melhor aguardar!"
#define STOP "Pare!"

static unsigned int duration_us = 0;

static unsigned int now_us() {
    return to_us_since_boot(get_absolute_time());
}

static bool has_wait_time_reached(unsigned int limit) {
    return now_us() - duration_us > limit;
}

void on_button_press() {
    toggle_nightly_mode();
    if (is_nightly_mode()) set_state(get_state(), ATTENTION);
}

void core_task() {
    buttons_init(on_button_press);
    set_state(GREEN, STOP);
    while (true) {
        os_sleep_ms(100);
        switch (get_state()) {
            case GREEN:
                if (!has_wait_time_reached(GREEN_DURATION_US)) continue;
                duration_us = now_us();
                set_state(YELLOW, WAIT);
            break;
            case YELLOW:
                if (!has_wait_time_reached(YELLOW_DURATION_US)) continue;
                duration_us = now_us();
                set_state(RED, CROSS);
            break;
            case RED:
                if (!has_wait_time_reached(RED_DURATION_US)) continue;
                duration_us = now_us();
                set_state(GREEN, STOP);
            break;
        }
    }
}
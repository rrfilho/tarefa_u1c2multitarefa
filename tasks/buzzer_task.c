#include "buzzer_task.h"
#include <stdbool.h>
#include "osal.h"
#include "state.h"
#include "buzzer.h"

static void normal_buzzer() {
    switch (get_state()) {
        case GREEN:
            buzzer_set(true);
            os_sleep_ms(1000);
            buzzer_set(false);
            os_sleep_ms(500);
        break;
        case YELLOW:
            for (int i = 0; i < 5; i++) {
                buzzer_set(true);
                os_sleep_ms(100);
                buzzer_set(false);
                os_sleep_ms(100);
            }
        break;
        case RED:
            buzzer_set(true);
            os_sleep_ms(500);
            buzzer_set(false);
            os_sleep_ms(1500);
        break;
    }
}

static void nightly_buzzer() {
    buzzer_set(true);
    os_sleep_ms(2000);
    buzzer_set(false);
    os_sleep_ms(2000);
}

void buzzer_task() {
    buzzer_init();
    while (true) {
        if (is_nightly_mode()) nightly_buzzer();
        else normal_buzzer();
    }
}
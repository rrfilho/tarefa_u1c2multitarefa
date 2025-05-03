#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "libs/osal.h"
#include "libs/leds.h"
#include "libs/buttons.h"
#include "libs/display.h"
#include "libs/buzzer.h"

volatile bool mode = false;
int state = 0;
char* message;

void normal_semaphore() {
    os_sleep_ms(1000);
    switch (state) {
        case 0:
            leds_set_red(false);
            leds_set_green(true);
            state = 1;
            message = "Pare!";
        break;
        case 10:
            leds_set_green(false);
            leds_set_yellow(true);
            state = 11;
            message = "Melhor aguardar!";
        break;
        case 13:
            leds_set_yellow(false);
            leds_set_red(true);
            state = 14;
            message = "Atravesse!";
        break;
        default: state = (state + 1)%24;
    }
}

void nightly_semaphore() {
    message = "Atencao";
    leds_unset_all();
    leds_set_yellow(true);
    os_sleep_ms(500);
    leds_set_yellow(false);
    os_sleep_ms(500);
}

void semaphore_task() {
    while (true) {
        if (mode) normal_semaphore();
        else nightly_semaphore();
    }
}

void display_task() {
    int counter = 0;
    while (true) {
        display_update(message);
        printf("Display Counter\n");
        os_sleep_ms(1000);
    }
}

void normal_buzzer() {
    switch (state) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            buzzer_set(true);
            os_sleep_ms(1000);
            buzzer_set(false);
            os_sleep_ms(500);
        break;
        case 11:
        case 12:
            for (int i = 0; i < 5; i++) {
                buzzer_set(true);
                os_sleep_ms(100);
                buzzer_set(false);
                os_sleep_ms(100);
            }
        break;
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
            buzzer_set(true);
            os_sleep_ms(500);
            buzzer_set(false);
            os_sleep_ms(1500);
        break;
    }
}

void nightly_buzzer() {
    buzzer_set(true);
    os_sleep_ms(2000);
    buzzer_set(false);
    os_sleep_ms(2000);
}

void buzzer_task() {
    while (true) {
        if (mode) normal_buzzer();
        else nightly_buzzer();
    }
}

void on_button_pressed() {
    mode = !mode;
}

void init() {
    stdio_init_all();
    leds_init();
    buttons_init(on_button_pressed);
    display_init();
    buzzer_init();
}

int main() {
    init();
    os_create_task(semaphore_task, "Semaphore Task");
    os_create_task(display_task, "Display Task");
    os_create_task(buzzer_task, "Buzzer Task");
    os_start();
}

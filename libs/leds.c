#include "leds.h"
#include <stdbool.h>
#include "pico/stdlib.h"

#define GREEN_LED_PIN 11
#define RED_LED_PIN 13

void leds_init() {
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
}

void leds_set_red(bool status) {
    gpio_put(RED_LED_PIN, status);
}

void leds_set_yellow(bool status) {
    leds_set_green(status);
    leds_set_red(status);
}

void leds_set_green(bool status) {
    gpio_put(GREEN_LED_PIN, status);
}

void leds_unset_all() {
    leds_set_green(false);
    leds_set_yellow(false);
    leds_set_red(false);
}
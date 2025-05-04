#include "led_matrix.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.h"
#include <stdio.h>

#define PIXELS 25
#define LED_MATRIX_PIN 7
#define RED 3342336
#define YELLOW 858980352
#define GREEN 855638016
#define ON 1
#define OFF 0
static const uint MAP[PIXELS] = {
    24,23,22,21,20,
    15,16,17,18,19,
    14,13,12,11,10,
     5, 6, 7, 8, 9,
     4, 3, 2, 1, 0
};
static const uint RED_MAP[PIXELS] = {
    OFF,  ON,  ON,  ON, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF, OFF, OFF, OFF, OFF,
    OFF, OFF, OFF, OFF, OFF
};
static const uint YELLOW_MAP[PIXELS] = {
    OFF, OFF, OFF, OFF, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF, OFF, OFF, OFF, OFF
};
static const uint GREEN_MAP[PIXELS] = {
    OFF, OFF, OFF, OFF, OFF,
    OFF, OFF, OFF, OFF, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF,  ON,  ON,  ON, OFF,
    OFF,  ON,  ON,  ON, OFF
};
static const PIO PIO_ID = pio0;
static uint sm;

void led_matrix_init() {
    set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(PIO_ID, &pio_matrix_program);
    sm = pio_claim_unused_sm(PIO_ID, true);
    pio_matrix_program_init(PIO_ID, sm, offset, LED_MATRIX_PIN);
}

static void set_leds(const uint* map, int color) {
    for (uint i = 0; i < PIXELS; i++) {
        uint index = MAP[i];
        uint led_value = map[index];
        pio_sm_put_blocking(PIO_ID, sm, led_value == ON ? color : OFF);
    }
}

static void led_matrix_clear() {
    for (uint i = 0; i < PIXELS; i++)
        pio_sm_put_blocking(PIO_ID, sm, OFF);
}

void led_matrix_set_red(bool status) {
    if(status) set_leds(RED_MAP, RED);
    else led_matrix_clear();
}

void led_matrix_set_yellow(bool status) {
    if(status) set_leds(YELLOW_MAP, YELLOW);
    else led_matrix_clear();
}

void led_matrix_set_green(bool status) {
    if(status) set_leds(GREEN_MAP, GREEN);
    else led_matrix_clear();
}
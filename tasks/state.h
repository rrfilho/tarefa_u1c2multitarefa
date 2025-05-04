#ifndef STATE_H
#define STATE_H

#include <stdbool.h>

typedef enum {
    GREEN = 0,
    YELLOW = 1,
    RED = 2
} State;

void set_state(State state, char* message);

State get_state();

void toggle_nightly_mode();

bool is_nightly_mode();

char* get_message();

#endif
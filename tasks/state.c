#include "state.h"
#include <stdbool.h>

static State _state = GREEN;
static bool _nightly_mode = false;
static char* _message;

void set_state(State state, char* message) {
    _state = state;
    _message = message;
}

State get_state() {
    return _state;
}

void toggle_nightly_mode() {
    _nightly_mode = !_nightly_mode;
}

bool is_nightly_mode() {
    return _nightly_mode;
}

char* get_message() {
    return _message;
}

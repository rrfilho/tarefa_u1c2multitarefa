#include "display_task.h"
#include <stdbool.h>
#include "osal.h"
#include "state.h"
#include "display.h"

void display_task() {
    display_init();
    while (true) {
        display_update(get_message());
    }
}
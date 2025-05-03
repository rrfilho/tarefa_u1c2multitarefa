// Operational System Abstraction Layer
#include "osal.h"
#include "FreeRTOS.h"
#include "task.h"

void os_sleep_ms(unsigned int duration) {
    vTaskDelay(pdMS_TO_TICKS(duration));
}

void os_create_task(task task, char* task_name) {
    xTaskCreate(task, task_name, configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
}

void os_start() {
    vTaskStartScheduler();
    panic_unsupported();
}
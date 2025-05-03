// Operational System Abstraction Layer
typedef void (*task)();

void os_sleep_ms(unsigned int duration);
void os_create_task(task task, char* task_name);
void os_start();

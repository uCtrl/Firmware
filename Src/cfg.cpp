#include "cfg.h"

#include "mbed.h"
#include "rtos.h"

osPriority CONTROLLER_PRIORITY = osPriorityNormal;
uint32_t CONTROLLER_STACK_SIZE = 256;

osPriority COM_DRIVER_PRIORITY = osPriorityHigh;
uint32_t COM_DRIVER_STACK_SIZE = 512;

osPriority TASK_HANDLER_PRIORITY = osPriorityBelowNormal;
uint32_t TASK_HANDLER_STACK_SIZE = 1024;

osPriority SENSOR_HANDLER_PRIORITY = osPriorityAboveNormal;
uint32_t SENSOR_HANDLER_STACK_SIZE = 256;

osPriority ACTUATOR_HANDLER_PRIORITY = osPriorityRealtime;
uint32_t ACTUATOR_HANDLER_STACK_SIZE = 256;

osPriority MESSAGE_HANDLER_PRIORITY = osPriorityNormal;
uint32_t MESSAGE_HANDLER_STACK_SIZE = 256;
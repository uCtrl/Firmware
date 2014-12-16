#ifndef THREAD_CFG_H_
#define THREAD_CFG_H_

#include "rtos.h"

//osPriorityIdle          = -3,          ///< priority: idle (lowest)
//osPriorityLow           = -2,          ///< priority: low
//osPriorityBelowNormal   = -1,          ///< priority: below normal
//osPriorityNormal        =  0,          ///< priority: normal (default)
//osPriorityAboveNormal   = +1,          ///< priority: above normal
//osPriorityHigh          = +2,          ///< priority: high
//osPriorityRealtime      = +3,          ///< priority: realtime (highest)

osPriority COM_DRIVER_IN_PRIORITY   = osPriorityHigh;
osPriority COM_DRIVER_OUT_PRIORITY  = osPriorityHigh;
osPriority MESSAGE_HANDLER_PRIORITY = osPriorityNormal;
osPriority DEVICE_HANDLER_PRIORITY  = osPriorityAboveNormal;
osPriority TASK_HANDLER_PRIORITY    = osPriorityBelowNormal;

const uint32_t COM_DRIVER_IN_STACK_SIZE     = 30000;
const uint32_t COM_DRIVER_OUT_STACK_SIZE    = 30000;
const uint32_t DEVICE_HANDLER_STACK_SIZE    = 5120;
const uint32_t TASK_HANDLER_STACK_SIZE      = 5120;
const uint32_t MESSAGE_HANDLER_STACK_SIZE   = 30000;
const uint32_t SOFT_RESET_STACK_SIZE        = 100;

unsigned char COM_DRIVER_IN_STACK   [COM_DRIVER_IN_STACK_SIZE];
unsigned char COM_DRIVER_OUT_STACK  [COM_DRIVER_OUT_STACK_SIZE];
unsigned char DEVICE_HANDLER_STACK  [DEVICE_HANDLER_STACK_SIZE];
unsigned char MESSAGE_HANDLER_STACK [MESSAGE_HANDLER_STACK_SIZE];
unsigned char TASK_HANDLER_STACK    [TASK_HANDLER_STACK_SIZE];
unsigned char SOFT_RESET_STACK      [SOFT_RESET_STACK_SIZE];

#endif /* THREAD_CFG_H_ */



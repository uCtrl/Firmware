#ifndef CFG_H_
#define CFG_H_

#include "rtos.h"

#define USE_LWIP        true
#define SERIAL_BAUD     9600
#define UDPSOCKET_PORT  7
#define COM_BUFFER_SIZE 255

//osPriorityIdle          = -3,          ///< priority: idle (lowest)
//osPriorityLow           = -2,          ///< priority: low
//osPriorityBelowNormal   = -1,          ///< priority: below normal
//osPriorityNormal        =  0,          ///< priority: normal (default)
//osPriorityAboveNormal   = +1,          ///< priority: above normal
//osPriorityHigh          = +2,          ///< priority: high
//osPriorityRealtime      = +3,          ///< priority: realtime (highest)

extern osPriority CONTROLLER_PRIORITY;
extern uint32_t CONTROLLER_STACK_SIZE;

extern osPriority COM_DRIVER_PRIORITY;
extern uint32_t COM_DRIVER_STACK_SIZE;

extern osPriority TASK_HANDLER_PRIORITY;
extern uint32_t TASK_HANDLER_STACK_SIZE;

extern osPriority SENSOR_HANDLER_PRIORITY;
extern uint32_t SENSOR_HANDLER_STACK_SIZE;

extern osPriority ACTUATOR_HANDLER_PRIORITY;
extern uint32_t ACTUATOR_HANDLER_STACK_SIZE;

extern osPriority MESSAGE_HANDLER_PRIORITY;
extern uint32_t MESSAGE_HANDLER_STACK_SIZE;


#endif /* CFG_H_ */


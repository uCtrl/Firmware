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

//PLC threads
osPriority PLC_DRIVER_IN_PRIORITY = osPriorityRealtime;
const uint32_t PLC_DRIVER_IN_STACK_SIZE = 2048;
unsigned char PLC_DRIVER_IN_STACK[PLC_DRIVER_IN_STACK_SIZE];

osPriority PLC_DRIVER_OUT_PRIORITY = osPriorityRealtime;
const uint32_t PLC_DRIVER_OUT_STACK_SIZE = 2048;
unsigned char PLC_DRIVER_OUT_STACK[PLC_DRIVER_OUT_STACK_SIZE];

osPriority PLC_HANDLER_PRIORITY = osPriorityAboveNormal;
const uint32_t PLC_HANDLER_STACK_SIZE = 4096;
unsigned char PLC_HANDLER_STACK[PLC_HANDLER_STACK_SIZE];

#endif /* CFG_H_ */


#ifndef CFG_H_
#define CFG_H_

//osPriorityIdle          = -3,          ///< priority: idle (lowest)
//osPriorityLow           = -2,          ///< priority: low
//osPriorityBelowNormal   = -1,          ///< priority: below normal
//osPriorityNormal        =  0,          ///< priority: normal (default)
//osPriorityAboveNormal   = +1,          ///< priority: above normal
//osPriorityHigh          = +2,          ///< priority: high
//osPriorityRealtime      = +3,          ///< priority: realtime (highest)

osPriority CONTROLLER_PRIORITY = osPriorityNormal;
uint32_t CONTROLLER_STACK_SIZE = 256;

osPriority COM_DRIVER_PRIORITY = osPriorityHigh;
uint32_t COM_DRIVER_STACK_SIZE = 512;

osPriority TASK_HANDLER_PRIORITY = osPriorityBelowNormal;
uint32_t TASK_HANDLER_STACK_SIZE = 512;

osPriority SENSOR_HANDLER_PRIORITY = osPriorityAboveNormal;
uint32_t SENSOR_HANDLER_STACK_SIZE = 256;

osPriority ACTUATOR_HANDLER_PRIORITY = osPriorityRealtime;
uint32_t ACTUATOR_HANDLER_STACK_SIZE = 256;

osPriority MESSAGE_HANDLER_PRIORITY = osPriorityNormal;
uint32_t MESSAGE_HANDLER_STACK_SIZE = 256;


#endif /* CFG_H_ */

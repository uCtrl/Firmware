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
int CONTROLLER_STACK_SIZE = 256;

osPriority COM_DRIVER_PRIORITY = osPriorityHigh;
int COM_DRIVER_STACK_SIZE = 512;

osPriority TASK_HANDLER_PRIORITY = osPriorityBelowNormal;
int TASK_HANDLER_STACK_SIZE = 1024;

osPriority SENSOR_HANDLER_PRIORITY = osPriorityAboveNormal;
int SENSOR_HANDLER_STACK_SIZE = 256;

osPriority ACTUATOR_HANDLER_PRIORITY = osPriorityRealtime;
int ACTUATOR_HANDLER_STACK_SIZE = 256;

osPriority MESSAGE_HANDLER_PRIORITY = osPriorityNormal;
int MESSAGE_HANDLER_STACK_SIZE = 256;


#endif /* CFG_H_ */

#ifndef CFG_H_
#define CFG_H_

#include "rtos.h"

#define FREESCALE_TEMP          false
#define PLATFORM_1              true
#define PLATFORM_2              true

#define MINIMALIST_PRINT        1
//#define DEBUG_PRINT             1
//#define DEBUG_CONDITIONS        1

#define BROADCAST_PORT          7;
#define FIRMWARE_VERSION        "1.0.0.0"
#define UDPSOCKET_PORT          7
#define USE_LWIP                true
#define SERIAL_BAUD             9600
#define COM_BUFFER_SIZE         1900
#define MSGHANDLER_MAIL_SIZE    10
#define COMDRIVER_OUT_MAIL_SIZE 10

#define DEFAULT_CONFIG          true
#define USE_BROADCAST           true
#define USE_MULTICAST           false
#define SEND_BROADCAST          true
#define SEND_MULTICAST          false

// Json packets approximate size
#define JSON_HEADER_SIZE        100
#define PLATFORM_JSON_SIZE      225
#define DEVICE_JSON_SIZE        300
#define SCENARIO_JSON_SIZE      125
#define TASK_JSON_SIZE          125
#define CONDITION_JSON_SIZE     300

#define SENSOR_LIST_LENGTH      10
#define ACTUATORS_LIST_LENGTH   10
#define PIN_NAME_LENGTH         2
//#define BUFFER_SIZE 255
//#define UCOM_BUFFER_SIZE 255

//#define PLATFORM LPC
#define PLATFORM FREESCALE

#define DELAY_BETWEEN_PLATFORM_BROADCASTS 5000

#define USE_DHCP                true
#define IP_ADDRESS              192.168.0.110

#endif /* CFG_H_ */


// For some reason, this define does not work. driverIn.cpp and driverOut.cpp needs to me modified
//#define MULTICAST_GRP =         "224.1.1.1"
//#define MULTICAST_PORT =        5007


//#define BROADCAST_PORT 58083; //Default port
//#define BROADCAST_PORT 55056; //PacketSender
//#define IP_ADDRESS          192.168.0.100

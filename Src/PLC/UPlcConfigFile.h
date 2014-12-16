#ifndef G3_PLC_CONFIG_FILE_H_
#define G3_PLC_CONFIG_FILE_H_

#include "mbed.h"
#include "TextString.h"

//#include "stdint.h"
//#include "stdlib.h"
//#include "string.h"


//#include "UPlcConfigFile.h"
//g3 plc type definition

#define byte unsigned char
#define BYTE unsigned char
#define CHAR char
#define UINT8 uint8_t
#define UINT16 uint16_t
#define UINT32 uint32_t
#define INT8 int8_t
#define INT16 int16_t
#define INT32 int32_t
#define TRUE true
#define FALSE false



//old parameters to be compliant
//TextString G3_NODE_MODE = "b";

//Plc serial config
#define PLC_SERIAL_BAUD_RATE 57600
//plcSerial.baud(PLC_SERIAL_BAUD_RATE);

//mails config
#define MAIL_LEN_UPLC_HANDLER 2

//queue
#define QUEUE_LEN_UPLC_DRIVER_IN 2

#define QUEUE_LEN_UPLC_DRIVER_OUT 2

//plc message header size
#define PLC_MESSAGE_HEADER_SIZE 4


//PLC Parameters
const TextString GMK_TS((char*)"");
const TextString PSK_TS((char*)"");
const TextString EXTENDED_ADDRESS((char*)"");
const TextString PRODUCT_ID((char*)"");

#define FIRST_DATA_TRANSFERT_LENGTH 139
extern char firstDataTransfert[FIRST_DATA_TRANSFERT_LENGTH];

#define RANDOM_SEED 42
#define DATA_PORT SCI_A
#define DIAG_PORT SCI_A

#define VENDOR_ID 0

#define TONEMASK_ID 0
#define TMR_FLAG '\0'
#define COH_FLAG '\0'
#define MODULATION '\0'
#define TX_LEVEL 1
#define BAND_VALUE '\0'


#endif /* G3_PLC_CONFIG_FILE_H_ */

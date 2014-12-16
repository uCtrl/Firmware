/*
 * UPlcDriverIn.h
 *
 *  Created on: Oct 7, 2014
 *      Author: uctrl
 */

#ifndef UPLC_DRIVER_IN_H_
#define UPLC_DRIVER_IN_H_

#include "mbed.h"
#include "rtos.h"
#include "UPlcConfigFile.h"
#include "Message.h"
#include "MessageHeader.h"

extern Mutex uart3Mutex;
extern Semaphore semQueueUPlcDriverIn;
extern Queue<Message, QUEUE_LEN_UPLC_DRIVER_IN>queueUPlcDriverIn;

class UPlcDriverIn
{
private:
	BYTE* readBytes(uint16_t length);
	RawSerial plcSerial;
public:
	UPlcDriverIn(PinName serialOut, PinName serialIn);
	void start();
};


#endif /* UPLC_DRIVER_IN_H_ */

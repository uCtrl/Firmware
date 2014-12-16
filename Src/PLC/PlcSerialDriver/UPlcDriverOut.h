/*
 * UPlcDriverOut.h
 *
 *  Created on: Oct 9, 2014
 *      Author: uctrl
 */

#ifndef UPLC_DRIVER_OUT_H_
#define UPLC_DRIVER_OUT_H_

#include "mbed.h"
#include "rtos.h"
#include "UPlcConfigFile.h"
#include "Message.h"

extern Semaphore semQueueUPlcDriverOut;
extern Queue<Message, QUEUE_LEN_UPLC_DRIVER_OUT>queueUPlcDriverOut;

class UPlcDriverOut
{
private:
	RawSerial plcSerial;
public:
	UPlcDriverOut(PinName serialOut, PinName serialIn);
	void start();
};


#endif /* UPLC_DRIVER_OUT_H_ */

/*
 * UPlcDriverOut.cpp
 *
 *  Created on: Oct 9, 2014
 *      Author: uctrl
 */

#include "UPlcDriverOut.h"
#include "UPlcDriverIn.h"

extern DigitalOut ledb;
extern Mutex indexMutexOutput;
extern volatile int masterIndexOutput;
extern Serial usbSerial;

Semaphore semQueueUPlcDriverOut(QUEUE_LEN_UPLC_DRIVER_OUT);
Queue<Message, QUEUE_LEN_UPLC_DRIVER_OUT>queueUPlcDriverOut;

UPlcDriverOut::UPlcDriverOut(PinName serialOut, PinName serialIn):
plcSerial(serialOut,serialIn)
{
	plcSerial.baud(PLC_SERIAL_BAUD_RATE);
}

void UPlcDriverOut::start()
{
	Message *message = NULL;
	BYTE *runningMessage = NULL;

	while(true)
	{
		osEvent evt = queueUPlcDriverOut.get();
		if (evt.status == osEventMessage)
		{
			/*ledb = !ledb;
			message = (Message*)evt.value.p;

			runningMessage = message->_Message;
			usbSerial.printf("messageSize:%d\r\n",message->_MessageSize);
			for(int i = 0;i<message->_MessageSize;i++)
			{
				uart3Mutex.lock();
				//plcSerial.putc(*runningMessage);
				plcSerial.putc(*message->_Message[i]);
				uart3Mutex.unlock();
				
				runningMessage++;
				
				// count serial bytes sended
				indexMutexOutput.lock();
				masterIndexOutput++;
				indexMutexOutput.unlock();
				
				// let a chance to serial read thread to read
				Thread::yield();
			}*/
			
			for(int i = 0; i<FIRST_DATA_TRANSFERT_LENGTH; i++)
		    {
		        uart3Mutex.lock();
				plcSerial.putc(firstDataTransfert[i]);
				uart3Mutex.unlock();
		    }
			
			// we are finished with message
			delete message;
			message = NULL;
			usbSerial.printf("message sent \r\n",message->_MessageSize);
			semQueueUPlcDriverOut.release();
		}
	}
	return;

}

/*
 * UPlcDriverIn.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: uctrl
 */

#ifdef TARGET_LPC1768
	#define ENABLE_UART_INTERRUPT NVIC_EnableIRQ(UART0_IRQn)
	#define DISABLE_UART_INTERRUPT NVIC_DisableIRQ(UART0_IRQn)
#else
	#define ENABLE_UART_INTERRUPT NVIC_EnableIRQ(UART3_RX_TX_IRQn)
	#define DISABLE_UART_INTERRUPT NVIC_DisableIRQ(UART3_RX_TX_IRQn)
#endif

#include "UPlcDriverIn.h"

extern DigitalOut ledr;
extern Serial usbSerial;
extern Mutex indexMutexInput;
extern volatile int masterIndexInput;

Mutex uart3Mutex;
Semaphore semQueueUPlcDriverIn(QUEUE_LEN_UPLC_DRIVER_IN);
Queue<Message, QUEUE_LEN_UPLC_DRIVER_IN>queueUPlcDriverIn;

osThreadId uPlcInThreadId;
#define SIGNAL_SERIAL_RX_TX 0x01

void uPlcDriverInSerialISR()
{
    // disable serial interrupt on uart3
    DISABLE_UART_INTERRUPT;
    osSignalSet(uPlcInThreadId,SIGNAL_SERIAL_RX_TX);
}

UPlcDriverIn::UPlcDriverIn(PinName serialOut, PinName serialIn)
:plcSerial(serialOut,serialIn)
{
	plcSerial.baud(PLC_SERIAL_BAUD_RATE);
	//plcSerial.format(8,SerialBase::None,1);
	//plcSerial.set_flow_control(Serial::Disabled,NC,NC);
	
	//setup interrupt
    uPlcInThreadId = Thread::gettid();
    plcSerial.attach(&uPlcDriverInSerialISR,Serial::RxIrq);
}

BYTE* UPlcDriverIn::readBytes(uint16_t length)
{
	if(length <= 0)
	{
		return NULL;
	}
	//usbSerial.printf("trying to read %u\r\n",(unsigned)length);
	BYTE *rtnBytes = new BYTE[length];
	BYTE *runningRtnBytes = rtnBytes;
	for(int i = 0;i<length;i++)
	{
		if(!plcSerial.readable())
        {
            ENABLE_UART_INTERRUPT;
            Thread::signal_wait(SIGNAL_SERIAL_RX_TX);   
        }
        uart3Mutex.lock();
		*runningRtnBytes = plcSerial.getc();
		usbSerial.putc(*runningRtnBytes);
		uart3Mutex.unlock();
		
		runningRtnBytes++;
		
		// count serial bytes received
		indexMutexInput.lock();
		masterIndexInput++;
		indexMutexInput.unlock();
	}
	return rtnBytes;
}

void UPlcDriverIn::start()
{
	BYTE * headerBuffer = NULL;
	BYTE * bodyBuffer = NULL;
	
	while(true)
	{
		MessageHeader messageHeader;
		headerBuffer = readBytes(PLC_MESSAGE_HEADER_SIZE);
		//usbSerial.printf("head:\n\r");

		messageHeader = headerBuffer;
		if (headerBuffer != NULL)
		{
			ledr = !ledr;
			//usbSerial.printf("PLC driver in Got Header:");
			//usbSerial.printf("message length: %u\r\n",(unsigned)messageHeader.GetMessageLength());
			//usbSerial.printf("header length: %u\r\n",(unsigned)messageHeader.HeaderLength());
			bodyBuffer = readBytes(messageHeader.GetMessageLength());
			
			if (bodyBuffer != NULL)
			{
				// usbSerial.printf("PLC driver IN, body read\r\n");
				// Got the body. Append header and body together as a message
				Message *message = new Message(messageHeader.HeaderLength(),
											   headerBuffer,
											   messageHeader.GetMessageLength(),
											   bodyBuffer);
				
				//Send message pointer to the queue
				semQueueUPlcDriverIn.wait(osWaitForever);
				queueUPlcDriverIn.put(message);
				usbSerial.printf("PLC driver IN, message sent\r\n");
			}
			else
			{
				usbSerial.printf("PLC driver IN, bodybuffer null\r\n");
			}
			
			// Odd message length, read one more padding byte
			if ((messageHeader.GetMessageLength() & 1) == 1)
			{
				delete [] readBytes(1);
			}
			//usbSerial.printf("endpadding");

			// Delete body buffer
			// Note: do not put into if(bodyBuffer != NULL) to not lag padding byte
			if (bodyBuffer != NULL)
			{
				delete [] bodyBuffer;
				bodyBuffer = NULL;
			}

			// Header buffer is not NULL, delete it
			delete [] headerBuffer;
			headerBuffer = NULL;
		}
		usbSerial.printf("PLC driver IN, end while\r\n");
	}
	return;
}

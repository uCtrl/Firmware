#include "cfg.h"
#include "mbed.h"
#include "rtos.h"


#include "UPlcDriverIn.h"
#include "UPlcDriverOut.h"
#include "UPlcHandler.h"

#define PLC_SERIAL_TX PTC17
#define PLC_SERIAL_RX PTC16

DigitalOut ledr(LED_RED);
DigitalOut ledg(LED_GREEN);
DigitalOut ledb(LED_BLUE);

void uPlcDriverInThread(void const *args) {
	UPlcDriverIn uPlcDriverIn(PLC_SERIAL_TX, PLC_SERIAL_RX);
	uPlcDriverIn.start();
}

void uPlcDriverOutThread(void const *args) {
	UPlcDriverOut uPlcDriverOut(PLC_SERIAL_TX, PLC_SERIAL_RX);
	uPlcDriverOut.start();
}

UPlcHandler uPlcHandler;

void uPlcHandlerThread(void const *args) {
	
	uPlcHandler.start();
}

//debugging usb
Serial usbSerial(USBTX,USBRX);

//those counters are used in UPlcDriverIn and UlcDriverOut to prevent race
// condition while incrementing bytes in/out counters
volatile int masterIndexInput = 0;
Mutex indexMutexInput;
volatile int masterIndexOutput = 0;
Mutex indexMutexOutput;

int main (void)
{
	usbSerial.baud(57600);
	ledg = 1;
	ledb = 1;
	ledr = 1;
	Thread plcOutThread(uPlcDriverOutThread,NULL,PLC_DRIVER_OUT_PRIORITY,PLC_DRIVER_OUT_STACK_SIZE,PLC_DRIVER_OUT_STACK);
	Thread plcInThread(uPlcDriverInThread,NULL,PLC_DRIVER_IN_PRIORITY,PLC_DRIVER_IN_STACK_SIZE,PLC_DRIVER_IN_STACK);
	Thread plcHandlerThread(uPlcHandlerThread,NULL,PLC_HANDLER_PRIORITY,PLC_HANDLER_STACK_SIZE,PLC_HANDLER_STACK);
	
	int temp_index_input;
	int temp_index_output;
	DigitalIn sw3(PTA4);
	int state = sw3.read();
	while(true)
	{
		
		indexMutexInput.lock();
		temp_index_input = masterIndexInput;
		indexMutexInput.unlock();
		
		indexMutexOutput.lock();
		temp_index_output = masterIndexOutput;
		indexMutexOutput.unlock();
		
		//usbSerial.putc('.');
		usbSerial.printf("plc input bytes:%d\r\n",temp_index_input);
		usbSerial.printf("plc output bytes:%d\r\n",temp_index_output);
		
		
		//if this led stop flashing, threads are blocked
		ledg = !ledg;
		Thread::wait(1000);
		
		//while we are cliking the switch we send a message through PLC (Not working yet!)
		if(state != sw3.read())
		{
			//uPlcHandler.connect();
			//uPlcHandler.sendMessage(Endpoint);
		}
	}
}

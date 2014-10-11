#include "mbed.h"
#include "rtos.h"
#include "cfg.h"

/*
#include "..\UtilityLibrary\CommandLineArguments.h"
#include "..\UtilityLibrary\GlobalVariables.h"
#include "..\CommonMessageLibrary\HostMessageFactory.h"
#include "..\G3_NetworkManagementLayer\G3_NetworkManagementLayer.h"
#include "..\UtilityLibrary\Log.h"
#include "G3_HostApplication.h"
#include "..\UtilityLibrary\TextString.h"*/

//#include "UPlcDriverIn.h"
//#include "UPlcDriverOut.h"
//#include "UPlcHandler.h"


#ifdef TARGET_LPC1768
#define LED_RED LED1
#define LED_GREEN LED2
#define LED_BLUE LED3
#endif

DigitalOut ledr(LED_RED);
DigitalOut ledg(LED_GREEN);
DigitalOut ledb(LED_BLUE);

//G3_NetworkManagementLayer plcNetwork = G3_NetworkManagementLayer();
//Serial uartPlc = Serial(PinName PTA2, PinName PTA1);
//Serial pc(USBTX,USBRX);
//UPlcDriver uPlcDriver;
/*
void uPlcDriverInThread(void const *args) {
	UPlcDriverIn uPlcDriverIn(PTA2, PTA1);
	uPlcDriverIn.start();
}

void uPlcDriverOutThread(void const *args) {
	UPlcDriverOut uPlcDriverOut(PTA2, PTA1);
	uPlcDriverOut.start();
}

void uPlcHandlerThread(void const *args) {
	UPlcHandler uPlcHandler;
	uPlcHandler.start();
}*/

int main (void)
{
	/*Thread plcInThread(uPlcDriverInThread,NULL,PLC_DRIVER_IN_PRIORITY,PLC_DRIVER_IN_STACK_SIZE);
	Thread plcOutThread(uPlcDriverOutThread,NULL,PLC_DRIVER_OUT_PRIORITY,PLC_DRIVER_OUT_STACK_SIZE);
	Thread plcHandlerThread(uPlcHandlerThread,NULL,PLC_HANDLER_PRIORITY,PLC_HANDLER_STACK_SIZE);
	*/
	ledg = 1;
	while(true)
	{
		ledg = !ledg;
		Thread::wait(1000);
	}
	/*
	char c;
	while(true)
	{
			 c = pc.getc();
			 //message queue
			 pc.putc(c);
			 ledg != ledg;
	}*/
	
	/*
	ledr = false;
	ledg = false;
	ledb = false;

	StringPair *arguments;

	//harcoded parameters
	arguments = new StringPair("xadd", "FF.FF.FF.FF.FF.FF.FF.04");
	args->Add(arguments);
	arguments = new StringPair("panId", "ACF8");
	args->Add(arguments);*/
/*
	//TODO #JF understanding pointer
	G3_NetworkManagementLayer network;
	TextString writeMsg = "";
	network.OpenSerialPort();
	network.StartProcess();
	network.StartNetwork();
	*/
/*
	//TODO #JF, to be added
	//THERE
	WaitForSingleObject(ShutdownEventHandle, INFINITE);

	return 0;
	*/
}

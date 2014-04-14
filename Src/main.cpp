/*
* main.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "mbed.h"
#include "rtos.h"
#include "UController.h"
#include "UComDriverIn.h"
#include "UComDriverOut.h"
#include "UMsgHandler.h"

DigitalOut led(LED_RED);

void startControllerThread(void const *args) {
	UController uController;
	uController.start();
}

void startComDriverInThread(void const *args) {
	UComDriverIn comDriverIn;
	comDriverIn.start();
}

void startComDriverOutThread(void const *args) {
	UComDriverOut comDriverOut;
	comDriverOut.start();
}

void startMsgHandlerThread(void const *args) {
	UMsgHandler msgHandler;
	msgHandler.start();
}

int main (void) {
	Thread controllerThread(startControllerThread);
    Thread comDriverInThread(startComDriverInThread);
    Thread comDriverOutThread(startComDriverOutThread);
    Thread msgHandlerThread(startMsgHandlerThread);

    led = true;
    while (true)
    {
    	//led = !led;
        Thread::wait(5000);
    }
}

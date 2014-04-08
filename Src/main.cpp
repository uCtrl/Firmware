#include "mbed.h"
#include "rtos.h"
#include "UController.h"
#include "UComDriver.h"
#include "FakeMessageHandler.h"
#include "UActuatorHandler.h"
#include "USensorHandler.h"

DigitalOut led(LED_RED);


void fakeMessageHandlerThread(void const *args) {

	FakeMessageHandler messageHandler = FakeMessageHandler();
	UActuatorHandler actuatorHandler = UActuatorHandler(&messageHandler);
	USensorHandler sensorHandler = USensorHandler(&messageHandler);
	messageHandler.initialize(&sensorHandler, &actuatorHandler);

	/*
    char tmp[10];
    sprintf(tmp,"%d",actuatorHandler.GetActuatorCount());
    messageHandler.SendMessage("Actuator count: ");
    messageHandler.SendMessage(tmp);
    messageHandler.SendMessage("\n\r");*/

	messageHandler.start();
}

int main (void) {

    Thread fakeMsgThread(fakeMessageHandlerThread);


    while (true)
    {
    	Thread::wait(700);
        led = !led;
    }
}

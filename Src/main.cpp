#include "mbed.h"
#include "rtos.h"
#include "cfg.h"
#include "UController.h"
#include "UComDriver.h"
#include "FakeMessageHandler.h"
#include "UActuatorHandler.h"
#include "USensorHandler.h"
#include "UMessageHandler.h"
#include "UTaskHandler.h"

#ifdef DEBUG_PRINT
extern Semaphore semMailUTaskHandler;
extern Mail<UTaskCfg, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;
#endif

/*
#include "USensorHandler.h"
#include "UActuatorHandler.h"
*/
DigitalOut led(LED_RED);
DigitalOut ledg(LED_GREEN);

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

void taskHandlerThread(void const *args) {
	UTaskHandler uTaskHandler;
	uTaskHandler.start();
}
/*
void sensorHandlerThread(void const *args) {
	USensorHandler uSensorHandler;
	uSensorHandler.start();
}

void actuatorHandlerThread(void const *args) {
	UActuatorHandler uActuatorHandler;
	uActuatorHandler.start();
}

void messageHandlerThread(void const *args) {
	UMessageHandler uMessageHandler;
	uMessageHandler.start();
}
*/

int main (void) {

    Thread fakeMsgThread(fakeMessageHandlerThread);


    while (true)
    {
    	Thread::wait(700);
        led = !led;
    }
    /*
	led = true;
	ledg = true;
    Thread ctrlThread(controllerThread,NULL,CONTROLLER_PRIORITY,CONTROLLER_STACK_SIZE);
    //Thread comThread(comDriverThread,NULL,COM_DRIVER_PRIORITY,COM_DRIVER_STACK_SIZE);

    Thread taskThread(taskHandlerThread,NULL,TASK_HANDLER_PRIORITY,TASK_HANDLER_STACK_SIZE);

    /*
    Thread sensorThread(sensorHandlerThread,NULL,SENSOR_HANDLER_PRIORITY,SENSOR_HANDLER_STACK_SIZE);
    Thread actuatorThread(actuatorHandlerThread,NULL,ACTUATOR_HANDLER_PRIORITY,ACTUATOR_HANDLER_STACK_SIZE);
    Thread messageThread(messageHandlerThread,NULL,MESSAGE_HANDLER_PRIORITY,MESSAGE_HANDLER_STACK_SIZE);
    *//*
    //    osEvent evt;
    //Thread::wait(5000);
    int i = 0;
    Thread::wait(1000);
    for(;;)
    {
    	/*evt = mail_box.get();
		if (evt.status == osEventMail) {
			UController *mail = (UController*)evt.value.p;
			//mail->start();

    	//for testing purpose
		#ifdef DEBUG_PRINT
    		semMailUTaskHandler.wait();
    		UTaskCfg *mail = mailUTaskHandler.alloc();
			if(mail != NULL)
			{
				i++;
				printf("%d",i);
				mail->taskCfgType = UACTION;
				mail->actionCfg.actuatorId = 123;
				printf("Send actuatorId:%lu\n\r", mail->actionCfg.actuatorId);
				mailUTaskHandler.put(mail);
				printf("Sent");
			}
			else
			{
				//error, should never happen with semaphore
				ledg = false;
				Thread::wait(500);
				ledg = true;
			}
		#endif
		printf("wait");
		Thread::wait(2000);
>>>>>>> fd99b4a90510ccf8d6bc99964d18b1d1a29ef698
	*/
}

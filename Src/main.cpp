/*
* main.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "mbed.h"
#include "rtos.h"
#include "cfg.h"
#include "UController.h"
<<<<<<< HEAD
#include "UComDriverIn.h"
#include "UComDriverOut.h"
#include "UMsgHandler.h"
=======
#include "UComDriver.h"
#include "UMessageHandler.h"
#include "UTaskHandler.h"
>>>>>>> f162662eaa6326c9bab8e4250162f27e6d4cd9fc

#ifdef DEBUG_PRINT
extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;
#endif

/*
#include "USensorHandler.h"
#include "UActuatorHandler.h"
*/
DigitalOut led(LED_RED);
<<<<<<< HEAD

void startControllerThread(void const *args) {
=======
DigitalOut ledg(LED_GREEN);



void controllerThread(void const *args)
{
>>>>>>> f162662eaa6326c9bab8e4250162f27e6d4cd9fc
	UController uController;
	uController.start();
}

<<<<<<< HEAD
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
=======
void comDriverThread(void const *args)
{
	UComDriver uComDriver;
	uComDriver.start();
}

void taskHandlerThread(void const *args)
{
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

int main (void)
{
	led = true;
	ledg = true;
    Thread ctrlThread(controllerThread,NULL,CONTROLLER_PRIORITY,CONTROLLER_STACK_SIZE);
    //Thread comThread(comDriverThread,NULL,COM_DRIVER_PRIORITY,COM_DRIVER_STACK_SIZE);

    Thread taskThread(taskHandlerThread,NULL,TASK_HANDLER_PRIORITY,TASK_HANDLER_STACK_SIZE);

    /*
    Thread sensorThread(sensorHandlerThread,NULL,SENSOR_HANDLER_PRIORITY,SENSOR_HANDLER_STACK_SIZE);
    Thread actuatorThread(actuatorHandlerThread,NULL,ACTUATOR_HANDLER_PRIORITY,ACTUATOR_HANDLER_STACK_SIZE);
    Thread messageThread(messageHandlerThread,NULL,MESSAGE_HANDLER_PRIORITY,MESSAGE_HANDLER_STACK_SIZE);
    */
    //    osEvent evt;
    //Thread::wait(5000);
    int i = 0;
    Thread::wait(1000);
    for(;;)
    {
    	led = false;
    	Thread::wait(500);
    	led = true;

    	//for testing purpose
		#ifdef DEBUG_PRINT
    		semMailUTaskHandler.wait();
    		UTaskRequest *mail = mailUTaskHandler.alloc();
			if(mail != NULL)
			{
				i++;
				printf("%d",i);
				mail->taskCfg.taskCfgType = UACTION;
				mail->taskCfg.actionCfg.actuatorId = 123;
				printf("Send actuatorId:%lu\n\r", mail->taskCfg.actionCfg.actuatorId);
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
>>>>>>> f162662eaa6326c9bab8e4250162f27e6d4cd9fc
    }
}

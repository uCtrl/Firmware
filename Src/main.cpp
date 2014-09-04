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
<<<<<<< HEAD

#include "UComDriverIn.h"
#include "UComDriverOut.h"
#include "UMsgHandler.h"
#include "UTaskHandler.h"
=======
#include "UComDriver.h"
#include "UMessageHandler.h"
#include "UTaskHandler.h"
#include "UTaskCfg.h"
>>>>>>> d62a46a7a802649d11e4ef59a988c82eb4851849
=======
#include "UComDriver.h"
#include "FakeMessageHandler.h"
#include "UActuatorHandler.h"
#include "USensorHandler.h"
#include "UMessageHandler.h"
#include "UTaskHandler.h"
#include "UTaskCfg.h"
>>>>>>> c75ecf48f273bd77a2bb1eaa8c7ad1c0feb7119f

#ifdef DEBUG_PRINT
extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;
#endif

/*
#include "USensorHandler.h"
#include "UActuatorHandler.h"
<<<<<<< HEAD
*/
<<<<<<< HEAD
DigitalOut led(LED_RED);
=======
DigitalOut ledr(LED_RED);
=======
*/
DigitalOut ledr(LED_RED);
>>>>>>> c75ecf48f273bd77a2bb1eaa8c7ad1c0feb7119f
DigitalOut ledg(LED_GREEN);
DigitalOut ledb(LED_BLUE);
>>>>>>> d62a46a7a802649d11e4ef59a988c82eb4851849

<<<<<<< HEAD
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

void startTaskHandlerThread(void const *args)
{
=======
//FakeMessageHandler messageHandler = FakeMessageHandler();
//UActuatorHandler actuatorHandler = UActuatorHandler(&messageHandler);
//USensorHandler sensorHandler = USensorHandler(&messageHandler);

/*void fakeMessageHandlerThread(void const *args) {
	messageHandler.initialize(&sensorHandler, &actuatorHandler);
	messageHandler.start();
}*/

void sensorPoolingThread(void const *args) {
	//sensorHandler.StartPoolingSensors();
}

void taskHandlerThread(void const *args)
{
>>>>>>> c75ecf48f273bd77a2bb1eaa8c7ad1c0feb7119f
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
<<<<<<< HEAD

<<<<<<< HEAD
int main (void) {
	Thread controllerThread(startControllerThread,NULL,CONTROLLER_PRIORITY,CONTROLLER_STACK_SIZE);
    Thread comDriverInThread(startComDriverInThread);
    Thread comDriverOutThread(startComDriverOutThread);
    Thread msgHandlerThread(startMsgHandlerThread);
    Thread taskThread(startTaskHandlerThread,NULL,TASK_HANDLER_PRIORITY,TASK_HANDLER_STACK_SIZE);
    /*
        Thread sensorThread(sensorHandlerThread,NULL,SENSOR_HANDLER_PRIORITY,SENSOR_HANDLER_STACK_SIZE);
        Thread actuatorThread(actuatorHandlerThread,NULL,ACTUATOR_HANDLER_PRIORITY,ACTUATOR_HANDLER_STACK_SIZE);
        Thread messageThread(messageHandlerThread,NULL,MESSAGE_HANDLER_PRIORITY,MESSAGE_HANDLER_STACK_SIZE);
	*/

    led = true;
    for(;;)
    {
    	//led = !led;
        Thread::wait(5000);

=======
=======
/*
>>>>>>> c75ecf48f273bd77a2bb1eaa8c7ad1c0feb7119f
int main (void)
{

    Thread fakeMsgThread(fakeMessageHandlerThread);
    Thread sensorThread(sensorPoolingThread);

    while (true)
    {
    	Thread::wait(700);
        led = !led;
    }
}*/

int main (void)
{
	ledr = false;
	ledg = false;
	ledb = false;

    //Thread ctrlThread(controllerThread,NULL,CONTROLLER_PRIORITY,CONTROLLER_STACK_SIZE);
    //Thread comThread(comDriverThread,NULL,COM_DRIVER_PRIORITY,COM_DRIVER_STACK_SIZE);

    Thread taskThread(taskHandlerThread,NULL,TASK_HANDLER_PRIORITY,TASK_HANDLER_STACK_SIZE);

    /*
    Thread sensorThread(sensorHandlerThread,NULL,SENSOR_HANDLER_PRIORITY,SENSOR_HANDLER_STACK_SIZE);
    Thread actuatorThread(actuatorHandlerThread,NULL,ACTUATOR_HANDLER_PRIORITY,ACTUATOR_HANDLER_STACK_SIZE);
    Thread messageThread(messageHandlerThread,NULL,MESSAGE_HANDLER_PRIORITY,MESSAGE_HANDLER_STACK_SIZE);
    *//*
    //    osEvent evt;
    //Thread::wait(5000);
	*/

    uint32_t i = 0;
    for(;;)
    {
    	/*ledr = false;
    	Thread::wait(100);
    	ledr = true;*/
    	//for testing purpose
		semMailUTaskHandler.wait();
		UTaskRequest *mail = mailUTaskHandler.alloc();
		if(mail != NULL)
		{
			if(i == 0)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UDEVICE;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 12;
				mail->taskCfg.parentId = 0;
				mailUTaskHandler.put(mail);
				printf("Sent Device %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 1)
			{

				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = USCENERY;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 7;
				mail->taskCfg.parentId = 12;
				mailUTaskHandler.put(mail);
				printf("Sent Scenery %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 2)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UTASK;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 10;
				mail->taskCfg.parentId = 7;
				mail->taskCfg.ActionValue = 124;
				mailUTaskHandler.put(mail);
				printf("Sent Task %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 3)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UCONDITION;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 34;
				mail->taskCfg.parentId = 10;
				mail->taskCfg.conditionCfg.sensorId = 1245;
				mail->taskCfg.conditionCfg.value = 934;
				mail->taskCfg.conditionCfg.operatorType = EQUAL;
				mailUTaskHandler.put(mail);
				printf("Sent Condition %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 4)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UDEVICE;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 7645;
				mail->taskCfg.parentId = 0;
				mailUTaskHandler.put(mail);
				printf("Sent Device %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 5)
			{

				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = USCENERY;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 93;
				mail->taskCfg.parentId = 7645;
				mailUTaskHandler.put(mail);
				printf("Sent Scenery %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 6)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UTASK;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 14;
				mail->taskCfg.parentId = 93;
				mail->taskCfg.ActionValue = 4933;
				mailUTaskHandler.put(mail);
				printf("Sent Task %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 7)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UTASK;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 73;
				mail->taskCfg.parentId = 7;
				mail->taskCfg.ActionValue = 1397592;
				mailUTaskHandler.put(mail);
				printf("Sent Task %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 8)
			{
				mail->taskRequestType = EVENT;
				mail->event.sensorId = 1245;
				mail->event.value = 934;
				mailUTaskHandler.put(mail);
				printf("Sent event from sensor %lu\n\r", mail->event.sensorId);
			}
			if(i == 9)
			{
				mail->taskRequestType = CONFIG;
				mail->taskCfg.taskCfgType = UCONDITION;
				mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
				mail->taskCfg.id = 3489;
				mail->taskCfg.parentId = 14;
				mail->taskCfg.conditionCfg.sensorId = 234;
				mail->taskCfg.conditionCfg.value = 2351;
				mail->taskCfg.conditionCfg.operatorType = EQUAL;
				mailUTaskHandler.put(mail);
				printf("Sent Condition %lu config\n\r", mail->taskCfg.id);
			}
			if(i == 10)
			{
				mail->taskRequestType = EVENT;
				mail->event.sensorId = 234;
				mail->event.value = 2351;
				mailUTaskHandler.put(mail);
				printf("Sent event from sensor %lu\n\r", mail->event.sensorId);
			}
			i++;
		}
		else
		{
			//error, should never happen with semaphore
			/*ledg = false;
			Thread::wait(500);
			ledg = true;*/
		}
		Thread::wait(200);
<<<<<<< HEAD
>>>>>>> d62a46a7a802649d11e4ef59a988c82eb4851849
    }

//    int i = 0;
//	Thread::wait(1000);
//	for(;;)
//	{
//		led = false;
//		Thread::wait(500);
//		led = true;
//
//		//for testing purpose
//		#ifdef DEBUG_PRINT
//			semMailUTaskHandler.wait();
//			UTaskRequest *mail = mailUTaskHandler.alloc();
//			if(mail != NULL)
//			{
//				i++;
//				printf("%d",i);
//				mail->taskCfg.taskCfgType = UACTION;
//				mail->taskCfg.actionCfg.actuatorId = 123;
//				printf("Send actuatorId:%lu\n\r", mail->taskCfg.actionCfg.actuatorId);
//				mailUTaskHandler.put(mail);
//				printf("Sent");
//			}
//			else
//			{
//				//error, should never happen with semaphore
//				ledg = false;
//				Thread::wait(500);
//				ledg = true;
//			}
//		#endif
//		printf("wait");
//		Thread::wait(2000);
//	}
=======
    }
>>>>>>> c75ecf48f273bd77a2bb1eaa8c7ad1c0feb7119f
}

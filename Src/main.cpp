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
#include "UComDriverIn.h"
#include "UComDriverOut.h"
#include "FakeMessageHandler.h"
#include "UActuatorHandler.h"
#include "USensorHandler.h"
#include "UMsgHandler.h"
#include "UTaskHandler.h"
#include "UPinUtils.h"
#include "UDeviceHandler.h"

#ifdef DEBUG_PRINT
//extern Semaphore semMailUTaskHandler;
//extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;
#endif

#ifdef TARGET_LPC1768
#define LED_RED LED1
#define LED_GREEN LED2
#define LED_BLUE LED3
#endif
DigitalOut ledr(UPinUtils::leds[0]);
DigitalOut ledg(UPinUtils::leds[1]);
DigitalOut ledb(UPinUtils::leds[2]);
DigitalOut ledw(UPinUtils::leds[3]);

UDeviceHandler uDeviceHandler = UDeviceHandler();

void startComDriverInThread(void const *args)
{
	UComDriverIn comDriverIn;
	comDriverIn.start();
}

void startComDriverOutThread(void const *args)
{
	UComDriverOut comDriverOut;
	comDriverOut.start();
}

void startMsgHandlerThread(void const *args)
{
	UMsgHandler msgHandler;
	msgHandler.start();
}

void sensorPoolingThread(void const *args)
{
	uDeviceHandler.StartPoolingSensors();
}

void taskHandlerThread(void const *args)
{
	UTaskHandler uTaskHandler = UTaskHandler(&uDeviceHandler);
	uTaskHandler.start();
}

int main (void)
{
    Thread comDriverInThread(startComDriverInThread);
    Thread comDriverOutThread(startComDriverOutThread);
    Thread msgHandlerThread(startMsgHandlerThread);

	Thread taskThread(taskHandlerThread,NULL,TASK_HANDLER_PRIORITY,TASK_HANDLER_STACK_SIZE);
	Thread sensorThread(sensorPoolingThread,NULL,SENSOR_HANDLER_PRIORITY,SENSOR_HANDLER_STACK_SIZE);

	//*/
	int i = 0;
	for(;;)
	{
		ledr = !ledr;
		Thread::wait(200);

		/*
		if(i <= 10) {
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
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);

				}
				if(i == 1)
				{

					mail->taskRequestType = CONFIG;
					mail->taskCfg.taskCfgType = USCENARIO;
					mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
					mail->taskCfg.id = 7;
					mail->taskCfg.parentId = 12;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 2)
				{
					mail->taskRequestType = CONFIG;
					mail->taskCfg.taskCfgType = UTASK;
					mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
					mail->taskCfg.id = 10;
					mail->taskCfg.parentId = 7;
					mail->taskCfg.ActionValue = 124;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
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
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 4)
				{
					mail->taskRequestType = CONFIG;
					mail->taskCfg.taskCfgType = UDEVICE;
					mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
					mail->taskCfg.id = 7645;
					mail->taskCfg.parentId = 0;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 5)
				{

					mail->taskRequestType = CONFIG;
					mail->taskCfg.taskCfgType = USCENARIO;
					mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
					mail->taskCfg.id = 93;
					mail->taskCfg.parentId = 7645;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 6)
				{
					mail->taskRequestType = CONFIG;
					mail->taskCfg.taskCfgType = UTASK;
					mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
					mail->taskCfg.id = 14;
					mail->taskCfg.parentId = 93;
					mail->taskCfg.ActionValue = 4933;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 7)
				{
					mail->taskRequestType = CONFIG;
					mail->taskCfg.taskCfgType = UTASK;
					mail->taskCfg.taskCfgMod = TASK_CFG_ADD;
					mail->taskCfg.id = 73;
					mail->taskCfg.parentId = 7;
					mail->taskCfg.ActionValue = 1397592;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 8)
				{
					mail->taskRequestType = EVENT;
					mail->event.sensorId = 1245;
					mail->event.value = 934;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
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
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				if(i == 10)
				{
					mail->taskRequestType = EVENT;
					mail->event.sensorId = 234;
					mail->event.value = 2351;
					mail->taskCfg.endpoint = NULL;
					mailUTaskHandler.put(mail);
				}
				i++;
			}
			else
			{
				//error, should never happen with semaphore
				//ledg = false;
				//Thread::wait(500);
				//ledg = true;
			}
			semMailUTaskHandler.release();

		}
		*/
	}
}

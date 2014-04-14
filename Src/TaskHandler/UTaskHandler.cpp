/*
 * UTaskHandler.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#include <TaskHandler/UTaskHandler.h>

Semaphore semMailUTaskHandler(MAIL_LEN_UTASKHANDLER);
Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;


void UTaskHandler::start()
{
	for(;;)
	{
		osEvent evt = mailUTaskHandler.get();
		if (evt.status == osEventMail)
		{
			UTaskRequest *mail = (UTaskRequest*)evt.value.p;
			if(mail->uTaskRequestType == EVENT)
			{
				this->handleTaskEvent(mail->event);
			}
			else if(mail->uTaskRequestType == CONFIG)
			{
				this->handleTaskCfg(mail->taskCfg);
			}
			mailUTaskHandler.free(mail);
			semMailUTaskHandler.release();
		}
	}
}

void UTaskHandler::handleTaskEvent(const UTaskEvent taskEvent)
{
	//TODO: TO IMPLEMENT
}

void UTaskHandler::handleTaskCfg(const UTaskCfg taskCfg)
{
	switch(taskCfg.taskCfgType)
	{
		case TASK_CFG_TYPE_NONE:
		{
			//TODO maybe an error
			break;
		}
		case USCENERY:
		{
			//TODO make something
			break;
		}
		case UTASK:
		{
			//TODO make something
			break;
		}
		case UCONDITION:
		{
			//TODO make something
			//use cfg->conditionCfg.sensorId for example
			break;
		}
		case UACTION:
		{
			#ifdef DEBUG_PRINT
				printf("Receive actuatorId:%lu\n\r",taskCfg.actionCfg.actuatorId);
			#endif
			break;
		}
	}
}

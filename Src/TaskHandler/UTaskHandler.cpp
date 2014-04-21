/*
 * UTaskHandler.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#include "UTaskHandler.h"

Semaphore semMailUTaskHandler(MAIL_LEN_UTASKHANDLER);
Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

//TODO remove next line
uint8_t testName[] = {'a','l','l','o'};


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
			//mainScenery = new UScenery();
			MainScenery = new UScenery(taskCfg.id,
										testName);
			#ifdef DEBUG_PRINT
				printf("Send sceneryId:%lu\n\r", MainScenery->SceneryID);
			#endif
			break;
		}
		case UTASK:
		{
			UTask *newTask = new UTask(taskCfg.id,
										testName);
			MainScenery->AddTask(newTask);
			#ifdef DEBUG_PRINT
				printf("Send TaskId:%lu\n\r", MainScenery->TaskList[MainScenery->ListIndex-1]->TaskID);
			#endif
			break;
		}
		case UCONDITION:
		{
			uint32_t i = 0;

			while(MainScenery->TaskList[i]->TaskID != taskCfg.parentId)
			{
				i++;
				if (i == MAX_CONDITION_NUMBER)
				{
					break;
				}
			}
			UCondition *newCondition = new UCondition(taskCfg.id,
													taskCfg.conditionCfg.sensorId,
													taskCfg.conditionCfg.value,
													taskCfg.conditionCfg.operatorType,
													testName);
			MainScenery->TaskList[i]->AddCondition(newCondition);
			break;
		}
		case UACTION:
		{
			#ifdef DEBUG_PRINT
				printf("Receive actuatorId:%lu\n\r",taskCfg.actionCfg.actuatorId);
			#endif

			uint32_t i = 0;

			while(MainScenery->TaskList[i]->TaskID != taskCfg.parentId)
			{
				i++;
				if (i == MAX_ACTION_NUMBER)
				{
					break;
				}
			}
			UAction *newAction = new UAction(taskCfg.id,
													taskCfg.actionCfg.actuatorId,
													taskCfg.actionCfg.value,
													testName);
			MainScenery->TaskList[i]->AddAction(newAction);
			break;
		}
	}
}

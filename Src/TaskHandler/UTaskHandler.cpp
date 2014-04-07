/*
 * UTaskHandler.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#include "UTaskHandler.h"

Semaphore semMailUTaskHandler(MAIL_LEN_UTASKHANDLER);
Mail<UTaskCfg, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

//TODO remove next line
uint8_t testName[] = {'a','l','l','o'};


void UTaskHandler::start()
{
	for(;;)
	{
		osEvent evt = mailUTaskHandler.get();
		if (evt.status == osEventMail)
		{
			UTaskCfg *mail = (UTaskCfg*)evt.value.p;
			switch(mail->taskCfgType)
			{
				case TASK_CFG_TYPE_NONE:
				{
					//TODO maybe an error
					break;
				}
				case USCENERY:
				{
					//mainScenery = new UScenery();
					MainScenery = new UScenery(mail->id,
												testName);
#ifdef DEBUG_PRINT
					printf("Send sceneryId:%lu\n\r", MainScenery->SceneryID);
#endif
					break;
				}
				case UTASK:
				{
					UTask *newTask = new UTask(mail->id,
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

					while(MainScenery->TaskList[i]->TaskID != mail->parentId)
					{
						i++;
						if (i == MAX_CONDITION_NUMBER)
						{
							break;
						}
					}
					UCondition *newCondition = new UCondition(mail->id,
															mail->conditionCfg.sensorId,
															mail->conditionCfg.value,
															mail->conditionCfg.operatorType,
															testName);
					MainScenery->TaskList[i]->AddCondition(newCondition);
					break;
				}
				case UACTION:
				{
					#ifdef DEBUG_PRINT
						printf("Receive actuatorId:%lu\n\r",mail->actionCfg.actuatorId);
					#endif

					uint32_t i = 0;

					while(MainScenery->TaskList[i]->TaskID != mail->parentId)
					{
						i++;
						if (i == MAX_ACTION_NUMBER)
						{
							break;
						}
					}
					UAction *newAction = new UAction(mail->id,
															mail->actionCfg.actuatorId,
															mail->actionCfg.value,
															testName);
					MainScenery->TaskList[i]->AddAction(newAction);
					break;
				}
			}
			mailUTaskHandler.free(mail);
			semMailUTaskHandler.release();
		}
	}
}

/*
 * UTaskHandler.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#include <TaskHandler/UTaskHandler.h>

Semaphore semMailUTaskHandler(MAIL_LEN_UTASKHANDLER);
Mail<UTaskCfg, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;


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
					//use mail->conditionCfg.sensorId for example
					break;
				}
				case UACTION:
				{
					#ifdef DEBUG_PRINT
						printf("Receive actuatorId:%lu\n\r",mail->actionCfg.actuatorId);
					#endif
					break;
				}
			}
			mailUTaskHandler.free(mail);
			semMailUTaskHandler.release();
		}
	}
}

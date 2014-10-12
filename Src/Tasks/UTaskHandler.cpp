/*
 * UTaskHandler.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#include "UTaskHandler.h"

Semaphore semMailUTaskHandler(MAIL_LEN_UTASKHANDLER);
Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

UTaskEvent EventPool[EVENT_POOL_SIZE];
int EventPoolIndex;


UTaskHandler::UTaskHandler()
{
	DeviceListIndex = 0;
}

UTaskHandler::UTaskHandler(USensorHandler* sensorHandler, UActuatorHandler* actuatorHandler) {
	DeviceListIndex = 0;
    m_sensorHandler = sensorHandler;
    m_actuatorHandler = actuatorHandler;
}

UTaskHandler::~UTaskHandler()
{
}

void UTaskHandler::start()
{
	for(;;)
	{
		osEvent evt = mailUTaskHandler.get();
		if (evt.status == osEventMail)
		{
			UTaskRequest *mail = (UTaskRequest*)evt.value.p;
			if(mail->taskRequestType == EVENT)
			{
				this->handleTaskEvent(mail->event);
			}
			else if(mail->taskRequestType == CONFIG)
			{
				this->handleTaskCfg(mail->taskCfg);
			}
			else
			{
#ifdef DEBUG_PRINT
				printf("Error Mail Type\n\r");
#endif
			}
			mailUTaskHandler.free(mail);
			semMailUTaskHandler.release();
		}

	}
}

void UTaskHandler::handleTaskEvent(const UTaskEvent taskEvent)
{
	// TODO : remove after tests
	printf("Task handler : Event from device %d : %d \r\n", taskEvent.sensorId, taskEvent.value);


	//AddEvent(taskEvent);
	//CheckDevice();
}

void UTaskHandler::handleTaskCfg(const UTaskCfg taskCfg)
{
	//TODO remove next line
	char testName[] = "testName";

	int parentFound = 0;
	switch(taskCfg.taskCfgType)
	{
		case TASK_CFG_TYPE_NONE:
		{
		#ifdef DEBUG_PRINT
			printf("Error Config Mail Type\n\r");
		#endif
			break;
		}
		case UDEVICE:
		{
			// TODO : remove after tests
			printf("Task handler : new device message recieved\r\n");
			UDevice* newDevice = new UDevice(taskCfg.id, testName);

			if(!AddDevice(newDevice))
			{
			#ifdef DEBUG_PRINT
				printf("Error Adding deviceId:%lu\n\r", newDevice->DeviceID);
			#endif
			}

			break;
		}
		case USCENARIO:
		{
			// TODO : remove after tests
			printf("Task handler : new scenario message recieved\r\n");

			for(int i = 0; i < DeviceListIndex; i++)
			{
				if(DeviceList[i]->DeviceID == taskCfg.parentId)
				{
					UScenario *newScenario = new UScenario(taskCfg.id,
														   testName);

					if(!DeviceList[i]->AddScenario(newScenario))
					{
					#ifdef DEBUG_PRINT
						printf("Error Adding sceneryId:%lu\n\r", newScenario->ScenarioID);
					#endif
					}
					parentFound = 1;
					break;
				}
			}

			if(!parentFound)
			{
			#ifdef DEBUG_PRINT
				printf("Error Device ID not found\n\r");
			#endif
			}
			break;
		}
		case UTASK:
		{
			// TODO : remove after tests
			printf("Task handler : new task message recieved\r\n");

			for(int i = 0; i < DeviceListIndex; i++)
			{
				for(int j = 0; j < DeviceList[i]->ScenarioListIndex; j++)
				{
					if(DeviceList[i]->ScenarioList[j]->ScenarioID == taskCfg.parentId)
					{
						UTask *newTask = new UTask(taskCfg.id,
													testName,
													taskCfg.ActionValue,
													DeviceList[i]->DeviceID);
						if(!DeviceList[i]->ScenarioList[j]->AddTask(newTask))
						{
						#ifdef DEBUG_PRINT
							printf("Error Adding TaskId:%lu\n\r", newTask->TaskID);
						#endif
						}

						parentFound = 1;
						break;
					}
				}
				if(parentFound)
				{
					break;
				}
			}

			if(!parentFound)
			{
			#ifdef DEBUG_PRINT
				printf("Error Scenario ID not found\n\r");
			#endif
			}


			break;
		}
		case UCONDITION:
		{
			// TODO : remove after tests
			printf("Task handler : new condition message recieved\r\n");

			for(int i = 0; i < DeviceListIndex; i++)
			{
				for(int j = 0; j < DeviceList[i]->ScenarioListIndex; j++)
				{
					for(int k = 0; k < DeviceList[i]->ScenarioList[j]->TaskListIndex; k++)
					{
						if(DeviceList[i]->ScenarioList[j]->TaskList[k]->TaskID == taskCfg.parentId)
						{
							UCondition *newCondition = new UCondition(taskCfg.id,
																		taskCfg.conditionCfg.sensorId,
																		taskCfg.conditionCfg.value,
																		taskCfg.conditionCfg.operatorType,
																		testName);
							if(!DeviceList[i]->ScenarioList[j]->TaskList[k]->AddCondition(newCondition))
							{
							#ifdef DEBUG_PRINT
								printf("Error Adding ConditionId:%lu\n\r", newCondition->ConditionID);
							#endif
							}
							parentFound = 1;
							break;
						}
					}

					if(parentFound)
					{
						break;
					}
				}

				if(parentFound)
				{
					break;
				}
			}

			if(!parentFound)
			{
			#ifdef DEBUG_PRINT
				printf("Error Task ID not found\n\r");
			#endif
			}
			break;
		}
	}
}

int UTaskHandler::AddDevice(UDevice *mDevice)
{
	USensorType type = Temperature;
	int pin = 2;
	int timeBetweenReads = 5000;

	if(m_sensorHandler->AddNewSensor(type, mDevice->DeviceID, pin, timeBetweenReads, mDevice->DeviceName)) {
		return 1;
	}
	else {
		return 0;
	}

	/*
	int retVal = 0;
	if (DeviceListIndex < MAX_DEVICE_NUMBER)
	{
		DeviceList[DeviceListIndex++] = mDevice;
		retVal = 1;
	}

	return retVal;*/
}


void UTaskHandler::DelDevice(int mDeviceID)
{
	int i = 0;

	for (; i < MAX_DEVICE_NUMBER; i++)
	{
		if (DeviceList[i]->DeviceID == mDeviceID)
		{
			int j = i;

			delete DeviceList[i];
			for (; j < MAX_DEVICE_NUMBER - 1; j++)
			{
				if (DeviceList[j + 1] != 0)
				{
					DeviceList[j] = DeviceList[j + 1];
				}
				else
				{
					break;
				}
			}
			delete DeviceList[MAX_DEVICE_NUMBER - 1];
			DeviceList[MAX_DEVICE_NUMBER - 1] = new UDevice;
			DeviceListIndex--;

			break;
		}
	}
}

int UTaskHandler::AddEvent(UTaskEvent mEvent)
{
	int retVal = 0;

	if (EventPoolIndex < EVENT_POOL_SIZE)
	{
		EventPool[EventPoolIndex].sensorId = mEvent.sensorId;
		EventPool[EventPoolIndex++].value = mEvent.value;
		retVal = 1;
	}
	return retVal;
}


void UTaskHandler::DelEvent(int mSensorID)
{
	for (int i = 0; i < EVENT_POOL_SIZE; i++)
	{
		if (EventPool[i].sensorId == mSensorID)
		{
			for (int j = i; j < EVENT_POOL_SIZE - 1; j++)
			{
				if (EventPool[j + 1].sensorId != 0)
				{
					EventPool[j].sensorId = EventPool[j + 1].sensorId;
					EventPool[j].value = EventPool[j + 1].value;
				}
				else
				{
					break;
				}
			}

			EventPool[EVENT_POOL_SIZE - 1].sensorId = 0;
			EventPool[EVENT_POOL_SIZE - 1].value = 0;
			EventPoolIndex--;

			break;
		}
	}
}

int UTaskHandler::CheckDevice()
{
	for (int i = 0; i < DeviceListIndex; i++)
	{
		DeviceList[i]->DoScenario();
	}

	return 0;
}

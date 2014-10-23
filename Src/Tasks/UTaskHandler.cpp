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
	m_platform = new UPlatform;
}

UTaskHandler::UTaskHandler(UDeviceHandler* deviceHandler) {
	DeviceListIndex = 0;
	m_deviceHandler = deviceHandler;
    m_platform = new UPlatform;
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
			else if(mail->taskRequestType == GET_INFO)
			{
				this->handleGetInfo(mail->taskCfg);
			}
			else if(mail->taskRequestType == SAVE_INFO)
			{
				this->handleSaveInfo(mail->taskCfg);
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


	int* deviceIds = m_deviceHandler->GetDeviceIds();
	for(int i = 0; i < m_deviceHandler->GetDeviceCount(); i++)
	{
		if(m_deviceHandler->GetDevice(deviceIds[i])->DeviceType == Actuator_Led)
		{
			m_deviceHandler->GetDevice(deviceIds[i])->DoScenario(taskEvent.sensorId, taskEvent.value);
		}
	}

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
			UDevice* newDevice = new UDevice(taskCfg.id, testName, Sensor_Temperature);

			/*
			if(!AddDevice(newDevice))
			{
			#ifdef DEBUG_PRINT
				printf("Error Adding deviceId:%lu\n\r", newDevice->DeviceID);
			#endif
			}*/

			break;
		}
		case USCENARIO:
		{
			// TODO : remove after tests
			printf("Task handler : new scenario message recieved\r\n");

			/*
			if(taskCfg.endpoint != NULL) {
				char* message = new char[36];
				strcpy(message, "New Scenario information sent.\0");
				UMsgHandler::SendMessage(message, taskCfg.endpoint);
				AddScenario(taskCfg.id, taskCfg.parentId, "scenarioName");
			}*/

			break;
		}
		case UTASK:
		{
			// TODO : remove after tests
			printf("Task handler : new task message recieved\r\n");

			for(int i = 0; i < DeviceListIndex; i++)
			{
				for(int j = 0; j < DeviceList[i]->ScenarioCount; j++)
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
				for(int j = 0; j < DeviceList[i]->ScenarioCount; j++)
				{
					for(int k = 0; k < DeviceList[i]->ScenarioList[j]->TaskCount; k++)
					{
						if(DeviceList[i]->ScenarioList[j]->TaskList[k]->TaskID == taskCfg.parentId)
						{
							UCondition *newCondition = new UCondition(	taskCfg.id,
																		testName,
																		taskCfg.conditionCfg.sensorId,
																		taskCfg.conditionCfg.value,
																		taskCfg.conditionCfg.operatorType);

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

void UTaskHandler::handleGetInfo(const UTaskCfg taskCfg)
{
	char* json;
	bool status;
	int messageType;
	int error;
	int size;
	UTaskCfgType type;

	switch(taskCfg.taskCfgType)
	{
		case UPLATFORM:
		{
			// TODO : remove after tests
			printf("Task handler : returning platform information\r\n");

			status = true;
			messageType = 2;
			error = 0;
			size = 1;

			json = m_platform->GetJSON();

			UMsgHandler::SendMessage(
					UJsonUtils::AddJsonGetShell(json, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
					taskCfg.endpoint);

			break;
		}
		case UDEVICE:
		{
			if(m_platform->id == taskCfg.parentId)
			{
				// TODO : remove after tests
				printf("Task handler : information of devices on platform %d\r\n", taskCfg.parentId);

				json = new char[200];
				memset(reinterpret_cast<void*>(json), 0, 200);

				int* deviceIds = m_deviceHandler->GetDeviceIds();
				for(int i = 0; i < m_deviceHandler->GetDeviceCount(); i++)
				{
					if(i != 0) {
						strcat(json, ",");
					}
					strcat(json, m_deviceHandler->GetDevice(deviceIds[i])->GetJSON());
				}

				status = true;
				messageType = 4;
				error = 0;
				size = m_deviceHandler->GetDeviceCount();

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell(json, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 4;
				error = 1;
				size = 0;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell("", taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}

			break;
		}
		case USCENARIO:
		{
			if(m_deviceHandler->GetDevice(taskCfg.parentId) != NULL) {
				// TODO : remove after tests
				printf("Task handler : information of scenarios on device %d\r\n",
						m_deviceHandler->GetDevice(taskCfg.parentId)->DeviceID);

				json = new char[200];
				memset(reinterpret_cast<void*>(json), 0, 200);

				printf("Number of scenarios: %d\r\n", m_deviceHandler->GetDevice(taskCfg.parentId)->ScenarioCount);

				for(int i = 0; i < m_deviceHandler->GetDevice(taskCfg.parentId)->ScenarioCount; i++)
				{
					if(i != 0) {
						strcat(json, ",");
					}
					strcat(json, m_deviceHandler->GetDevice(taskCfg.parentId)->ScenarioList[i]->GetJSON());
				}

				status = true;
				messageType = 6;
				error = 0;
				size = m_deviceHandler->GetDevice(taskCfg.parentId)->ScenarioCount;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell(json, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 8;
				error = 1;
				size =  0;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell("", taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}
			break;
		}
		case UTASK:
		{
			if(m_deviceHandler->GetScenario(taskCfg.parentId) != NULL) {
				// TODO : remove after tests
				printf("Task handler : information of tasks on scenario %d\r\n",
						m_deviceHandler->GetScenario(taskCfg.parentId)->ScenarioID);

				json = new char[200];
				memset(reinterpret_cast<void*>(json), 0, 200);

				printf("Number of tasks: %d\r\n", m_deviceHandler->GetScenario(taskCfg.parentId)->TaskCount);

				for(int i = 0; i < m_deviceHandler->GetScenario(taskCfg.parentId)->TaskCount; i++)
				{
					if(i != 0) {
						strcat(json, ",");
					}
					strcat(json, m_deviceHandler->GetScenario(taskCfg.parentId)->TaskList[i]->GetJSON());
				}

				status = true;
				messageType = 8;
				error = 0;
				size =  m_deviceHandler->GetScenario(taskCfg.parentId)->TaskCount;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell(json, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 8;
				error = 1;
				size =  0;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell("", taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}

			break;
		}
		case UCONDITION:
		{
			if(m_deviceHandler->GetTask(taskCfg.parentId) != NULL) {
				// TODO : remove after tests
				printf("Task handler : information of conditions on task %d\r\n",
						m_deviceHandler->GetTask(taskCfg.parentId)->TaskID);

				json = new char[200];
				memset(reinterpret_cast<void*>(json), 0, 200);

				printf("Number of conditions: %d\r\n", m_deviceHandler->GetTask(taskCfg.parentId)->ConditionListIndex);

				for(int i = 0; i < m_deviceHandler->GetTask(taskCfg.parentId)->ConditionListIndex; i++)
				{
					if(i != 0) {
						strcat(json, ",");
					}
					strcat(json, m_deviceHandler->GetTask(taskCfg.parentId)->ConditionList[i]->GetJSON());
				}

				status = true;
				messageType = 10;
				error = 0;
				size = m_deviceHandler->GetTask(taskCfg.parentId)->ConditionListIndex;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell(json, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 8;
				error = 1;
				size =  0;

				UMsgHandler::SendMessage(
						UJsonUtils::AddJsonGetShell("", taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType),
						taskCfg.endpoint);
			}

			break;
		}
		default:
		{
			printf("Task handler : default Get Event\r\n");
			break;
		}
	}
}

void UTaskHandler::handleSaveInfo(const UTaskCfg taskCfg)
{

	switch(taskCfg.taskCfgType)
	{
		case UPLATFORM:
		{
			// TODO : remove after tests
			printf("Task handler : saving platform information\r\n");
			printf("Task handler : platform : %d, %s, %s, %s\r\n",
					taskCfg.platform->id,
					taskCfg.platform->enabled,
					taskCfg.platform->name,
					taskCfg.platform->room);

			m_platform = taskCfg.platform;

			break;
		}
		case UDEVICE:
		{
			// TODO : remove after tests
			printf("Task handler : saving devices on platform %d\r\n", taskCfg.parentId);

			printf("Device name : %s\r\n", taskCfg.device->DeviceName);

			if(taskCfg.parentId == m_platform->id) {
				if(m_deviceHandler->GetDevice(taskCfg.device->DeviceID) == NULL)
				{
					m_deviceHandler->AddDevice(taskCfg.device);
				}
				else
				{
					// Replace the device with our new one
					m_deviceHandler->DeleteDevice(taskCfg.device);
					m_deviceHandler->AddDevice(taskCfg.device);
				}
			}

			break;
		}
		case USCENARIO:
		{
			// TODO : remove after tests
			printf("Task handler : saving scenarios on device %d\r\n", taskCfg.parentId);

			m_deviceHandler->GetDevice(taskCfg.parentId)->AddScenario(taskCfg.scenario);

			break;
		}
		case UTASK:
		{
			// TODO : remove after tests
			printf("Task handler : saving tasks on scenario %d\r\n",
					m_deviceHandler->GetScenario(taskCfg.parentId)->ScenarioID);

			m_deviceHandler->GetScenario(taskCfg.parentId)->AddTask(taskCfg.task);
			taskCfg.task->DeviceHandler = m_deviceHandler;

			break;
		}
		case UCONDITION:
		{
			// TODO : remove after tests
			printf("Task handler : saving conditions on task %d\r\n",
					m_deviceHandler->GetTask(taskCfg.parentId)->TaskID);

			m_deviceHandler->GetTask(taskCfg.parentId)->AddCondition(taskCfg.condition);
			taskCfg.condition->DeviceHandler = m_deviceHandler;

			break;
		}
		default:
		{
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

/*
int UTaskHandler::CheckDevice()
{
	for (int i = 0; i < DeviceListIndex; i++)
	{
		DeviceList[i]->DoScenario();
	}

	return 0;
}*/

void UTaskHandler::SendMessage(char* message, Endpoint* endpoint)
{
	//printf("Message : %s\r\n", message);

	UMsgHandlerMailType *mailOut = comDriverOutMail.alloc();

	if(USE_LWIP)
	{
		mailOut->endPoint->set_address(endpoint->get_address(), endpoint->get_port());
	}

	strcpy(mailOut->msg, message);
	//strcat(mailOut->msg, "\0");

	//comDriverOutMail.put(mailOut);

	delete endpoint;
}

/*
void UTaskHandler::AddScenario(int scenarioId, int parentId, char* scenarioName)
{
	int parentFound = 0;

	for(int i = 0; i < DeviceListIndex; i++)
	{
		if(DeviceList[i]->DeviceID == parentId)
		{
			UScenario *newScenario = new UScenario(scenarioId,
												   scenarioName);

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
}

void UTaskHandler::AddTask(int taskId, int parentId, char* status)
{

}

void UTaskHandler::AddCondition(int taskId, int parentId, int type)
{

}
*/

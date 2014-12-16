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
extern Serial usbSerial;

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
			else if(mail->taskRequestType == DELETE)
			{
				this->handleDelete(mail->taskCfg);
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
				usbSerial.printf("Error Mail Type\n\r");
#endif
			}
			mailUTaskHandler.free(mail);
			semMailUTaskHandler.release();
		}
	}
}

void UTaskHandler::handleTaskEvent(const UTaskEvent taskEvent)
{

#ifdef MINIMALIST_PRINT
	usbSerial.printf("Task handler : Event from device %d : %f \r\n", taskEvent.sensorId, taskEvent.value);
#endif

	// If the device is on this platform
	if(m_deviceHandler->GetDevice(taskEvent.sensorId) != NULL) 
	{
		char JSON[100] = {0};
	
		strcpy(JSON, "{\"messageType\":21,\"size\":1,\"sensorId\":");
		char buf1[10];
		sprintf(buf1, "%d", taskEvent.sensorId);
		strcat(JSON, buf1);
	
		strcat(JSON, ", \"value\":");
		char buf2[10];
		sprintf(buf2, "%f", taskEvent.value);
		strcat(JSON, buf2);
	
		strcat(JSON, "}");
		
		UMsgHandler::SendBroadcast(JSON);
	}

	int deviceIds[SENSOR_LIST_LENGTH+ACTUATORS_LIST_LENGTH] = {0};
	m_deviceHandler->GetDeviceIds(deviceIds);
	
	// Get all the devices on the current platform
	for(int i = 0; i < m_deviceHandler->GetDeviceCount(); i++)
	{
		UDevice* device = m_deviceHandler->GetDevice(deviceIds[i]);
		
		if(device->DeviceType == Actuator_Switch ||
		   device->DeviceType == Actuator_RGB ||
		   device->DeviceType == Actuator_LedsFlow)
		{
			int updatedConditions = m_deviceHandler->UpdateConditions(taskEvent.sensorId, taskEvent.value);
#ifdef DEBUG_PRINT
			usbSerial.printf("Updated %d conditions related to sensor %d\r\n", updatedConditions, taskEvent.sensorId);
#endif
			int nbOfScenariosCompleted = device->DoScenario(taskEvent.sensorId);
			
#ifdef DEBUG_PRINT
			usbSerial.printf("Completed %d scenarios.\r\n", nbOfScenariosCompleted);
#endif

			// Update the last value recieved from the sensor and broadcast
			if(device->CurrentValue != taskEvent.value) 
			{
				device->CurrentValue = taskEvent.value;
			}
		}
	}
}

void UTaskHandler::handleDelete(const UTaskCfg taskCfg)
{
	int messageType;
	bool success = false;
	char type[15] = {0};
	
	switch(taskCfg.taskCfgType)
	{
		case UDEVICE:
		{
#ifdef DEBUG_PRINT
			usbSerial.printf("Task handler : Deleting device %d\r\n", taskCfg.parentId);
#endif
			messageType = 34;
			success = m_deviceHandler->DeleteDevice(taskCfg.parentId);
			strcpy(type, "deviceId");
			break;
		}
		case USCENARIO:
		{
#ifdef DEBUG_PRINT
			usbSerial.printf("Task handler : Deleting scenario %d\r\n", taskCfg.parentId);
#endif
			messageType = 36;
			success = m_deviceHandler->DeleteScenario(taskCfg.parentId);
			strcpy(type, "scenarioId");
			break;
		}
		case UTASK:
		{
#ifdef DEBUG_PRINT
			usbSerial.printf("Task handler : Deleting task %d\r\n", taskCfg.parentId);
#endif
			messageType = 38;
			success = m_deviceHandler->DeleteTask(taskCfg.parentId);
			strcpy(type, "taskId");
			break;
		}
		case UCONDITION:
		{
#ifdef DEBUG_PRINT
			usbSerial.printf("Task handler : Deleting condition %d\r\n", taskCfg.parentId);
#endif
			messageType = 40;
			success = m_deviceHandler->DeleteCondition(taskCfg.parentId);
			strcpy(type, "conditionId");
			break;
		}
		default:
		{
			messageType = -1;
			strcpy(type, "error");
			usbSerial.printf("Task handler : default Get Event\r\n");
			break;
		}
	}
	
	char JSON[100] = {0};
	
	strcpy(JSON, "{\"messageType\":");
	char buf1[10];
	sprintf(buf1, "%d", messageType);
	strcat(JSON, buf1);
	
	strcat(JSON, ",\"");
	strcat(JSON, type);
	strcat(JSON, "\":\"");
	char buf2[10];
	sprintf(buf2, "%d", taskCfg.parentId);
	strcat(JSON, buf2);
	
	strcat(JSON, "\", \"success\":");
	if(success)
		strcat(JSON, "true");
	else
		strcat(JSON, "false");
	
	strcat(JSON, "}");
	
	UMsgHandler::SendMessage(JSON, taskCfg.endpoint);
}

void UTaskHandler::handleGetInfo(const UTaskCfg taskCfg)
{
	bool status;
	int messageType;
	int error;
	int size;

	switch(taskCfg.taskCfgType)
	{
		case UPLATFORM:
		{
#ifdef DEBUG_PRINT
			usbSerial.printf("Task handler : returning platform information\r\n");
#endif

			status = true;
			messageType = 2;
			error = 0;
			size = 1;

			char jsonToSend[COM_BUFFER_SIZE] = {0};
			
			m_platform->GetJSON(jsonToSend);
			
			UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
			UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);

			break;
		}
		case UDEVICE:
		{
			if(m_platform->Id == taskCfg.parentId)
			{
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : information of devices on platform %d\r\n", taskCfg.parentId);
#endif

				int deviceIds[SENSOR_LIST_LENGTH+ACTUATORS_LIST_LENGTH] = {0};
				m_deviceHandler->GetDeviceIds(deviceIds);
				size = m_deviceHandler->GetDeviceCount();
	
				char jsonToSend[COM_BUFFER_SIZE] = {0};
							
				for(int i = 0; i < size; i++)
				{
					if(i != 0) {
						strcat(jsonToSend, ",");
					}
					char JSON[DEVICE_JSON_SIZE] = {0};
					m_deviceHandler->GetDevice(deviceIds[i])->GetJSON(JSON);
					strcat(jsonToSend, JSON);
				}

				status = true;
				messageType = 4;
				error = 0;

				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 4;
				error = 1;
				size = 0;

				char jsonToSend[COM_BUFFER_SIZE] = {0};
				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}

			break;
		}
		case USCENARIO:
		{
			if(m_deviceHandler->GetDevice(taskCfg.parentId) != NULL) {
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : information of scenarios on device %d\r\n", m_deviceHandler->GetDevice(taskCfg.parentId)->DeviceID);
#endif

				size = m_deviceHandler->GetDevice(taskCfg.parentId)->ScenarioCount;
				
				char jsonToSend[COM_BUFFER_SIZE] = {0};

				for(int i = 0; i < size; i++)
				{
					if(i != 0) {
						strcat(jsonToSend, ",");
					}
					char JSON[SCENARIO_JSON_SIZE] = {0};
					m_deviceHandler->GetDevice(taskCfg.parentId)->ScenarioList[i]->GetJSON(JSON);
					strcat(jsonToSend, JSON);
				}

				status = true;
				messageType = 6;
				error = 0;
				
				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 8;
				error = 1;
				size =  0;

				char jsonToSend[COM_BUFFER_SIZE] = {0};
				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}
			break;
		}
		case UTASK:
		{
			if(m_deviceHandler->GetScenario(taskCfg.parentId) != NULL) {
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : information of tasks on scenario %d\r\n", taskCfg.parentId);
#endif

				size =  m_deviceHandler->GetScenario(taskCfg.parentId)->TaskCount;
				
				char jsonToSend[COM_BUFFER_SIZE] = {0};

				for(int i = 0; i < size; i++)
				{
					if(i != 0) {
						strcat(jsonToSend, ",");
					}
					char JSON[TASK_JSON_SIZE] = {0};
					m_deviceHandler->GetScenario(taskCfg.parentId)->TaskList[i]->GetJSON(JSON);
					strcat(jsonToSend, JSON);
				}

				status = true;
				messageType = 8;
				error = 0;
				
				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 8;
				error = 1;
				size =  0;

				char jsonToSend[COM_BUFFER_SIZE] = {0};
				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}

			break;
		}
		case UCONDITION:
		{
			UTask* task = m_deviceHandler->GetTask(taskCfg.parentId);
			if(task != NULL) {
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : information of conditions on task %d\r\n",	task->TaskID);
#endif
				size = task->ConditionListIndex;
				
				char jsonToSend[COM_BUFFER_SIZE] = {0};

				for(int i = 0; i < size; i++)
				{
					if(i != 0) {
						strcat(jsonToSend, ",");
					}
					char JSON[CONDITION_JSON_SIZE] = {0};
					task->ConditionList[i]->GetJSON(JSON);
					strcat(jsonToSend, JSON);
				}
				
				status = true;
				messageType = 10;
				error = 0;

				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}
			else
			{
				status = false;
				messageType = 8;
				error = 1;
				size =  0;

				char jsonToSend[COM_BUFFER_SIZE] = {0};
				UJsonUtils::AddJsonGetShell(jsonToSend, taskCfg.parentId, status, error, messageType, size, taskCfg.taskCfgType, taskCfg.messageId);
				UMsgHandler::SendMessage(jsonToSend,taskCfg.endpoint);
			}

			break;
		}
		default:
		{
			usbSerial.printf("Task handler : default Get Event\r\n");
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
#ifdef DEBUG_PRINT
			usbSerial.printf("Task handler : saving platform information\r\n");
#endif
			delete m_platform;
			m_platform = taskCfg.platform;
			m_platform->LastUpdated = time(NULL);

			break;
		}
		case UDEVICE:
		{
			if(taskCfg.parentId == m_platform->Id) 
			{
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : saving device %d on platform %d\r\n", taskCfg.device->DeviceID, taskCfg.parentId);
#endif
				UDevice* device = m_deviceHandler->GetDevice(taskCfg.device->DeviceID);
				if(device == NULL)
				{
					taskCfg.device->LastUpdated = time(NULL);
					m_deviceHandler->AddDevice(taskCfg.device);
				}
				else
				{
					device->DeviceType = taskCfg.device->DeviceType;
					device->DeviceName = taskCfg.device->DeviceName;					
					device->Description = taskCfg.device->Description;
					device->MaxValue = taskCfg.device->MaxValue;
					device->MinValue = taskCfg.device->MinValue;
					device->Precision = taskCfg.device->Precision;
					device->Status = taskCfg.device->Status;
					device->UnitLabel = taskCfg.device->UnitLabel;
					device->Enabled = taskCfg.device->Enabled;
					device->LastUpdated = time(NULL);
					
					if(device->DeviceType == Actuator_Switch || device->DeviceType == Actuator_RGB || device->DeviceType == Actuator_LedsFlow)
					{
						m_deviceHandler->SetActuatorValue(taskCfg.device->DeviceID, taskCfg.device->Value.c_str());
					}
					
					delete taskCfg.device;
				}
			}

			break;
		}
		case USCENARIO:
		{
			if(m_deviceHandler->GetDevice(taskCfg.parentId) != NULL) 
			{
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : saving scenario %d on device %d\r\n", taskCfg.scenario->ScenarioID, taskCfg.parentId);
#endif
				UScenario* scenario = m_deviceHandler->GetScenario(taskCfg.scenario->ScenarioID);
				if(scenario == NULL)
				{
					taskCfg.scenario->LastUpdated = time(NULL);
					m_deviceHandler->GetDevice(taskCfg.parentId)->AddScenario(taskCfg.scenario);
				} 
				else 
				{					
					scenario->ScenarioName = taskCfg.scenario->ScenarioName;
					scenario->DeviceId = taskCfg.scenario->DeviceId;
					scenario->Enabled = taskCfg.scenario->Enabled;
					scenario->LastUpdated = time(NULL);	
					
					delete taskCfg.scenario;		
				}
			}

			break;
		}
		case UTASK:
		{
			UScenario* scenario = m_deviceHandler->GetScenario(taskCfg.parentId);
			if(scenario != NULL) 
			{
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : saving task %d on scenario %d\r\n", taskCfg.task->TaskID, m_deviceHandler->GetScenario(taskCfg.parentId)->ScenarioID);
#endif
				UTask* task = m_deviceHandler->GetTask(taskCfg.task->TaskID);
				if(task == NULL)
				{
					taskCfg.task->LastUpdated = time(NULL);
					
					// Add the device id to the task because it needs it
					taskCfg.task->DeviceID = scenario->DeviceId;
					m_deviceHandler->GetScenario(taskCfg.parentId)->AddTask(taskCfg.task);
					taskCfg.task->DeviceHandler = m_deviceHandler;		
				} 
				else 
				{
					task->Enabled = taskCfg.task->Enabled;
					task->LastUpdated =  time(NULL);
					task->ActionValue = taskCfg.task->ActionValue;
					
					delete taskCfg.task;	
				}
				
			}

			break;
		}
		case UCONDITION:
		{
			if(m_deviceHandler->GetTask(taskCfg.parentId) != NULL) 
			{
#ifdef DEBUG_PRINT
				usbSerial.printf("Task handler : saving condition %d on task %d\r\n",taskCfg.condition->ConditionId, taskCfg.parentId);
#endif
				UCondition* condition = m_deviceHandler->GetCondition(taskCfg.condition->ConditionId);
				if(condition == NULL)
				{
					taskCfg.condition->LastUpdated = time(NULL);
					
					m_deviceHandler->GetTask(taskCfg.parentId)->AddCondition(taskCfg.condition);
					taskCfg.condition->DeviceHandler = m_deviceHandler;							
				}
				else
				{
					condition->ConditionId = taskCfg.condition->ConditionId;
					condition->ConditionType = taskCfg.condition->ConditionType;
					condition->ComparisonType = taskCfg.condition->ComparisonType;
					condition->EndValue = taskCfg.condition->EndValue;
					condition->BeginValue = taskCfg.condition->BeginValue;
					condition->DeviceId = taskCfg.condition->DeviceId;
					condition->Enabled = taskCfg.condition->Enabled;
					condition->LastUpdated = time(NULL);	
					
					delete taskCfg.condition;	
				}
			}
			

			break;
		}
		default:
		{
			break;
		}
	}
}

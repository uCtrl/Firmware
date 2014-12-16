#include "UScenario.h"
#include "UTask.h"

extern Serial usbSerial;

UScenario::UScenario()
{
	ScenarioID = 0;
	TaskCount = 0;

	for(int i = 0; i < MAX_TASK_NUMBER; i++)
	{
		TaskList[i] = NULL;
	}
}

UScenario::UScenario(int mScenarioID, string mScenarioName, bool enabled, int lastUpdated, int deviceId)
{
#ifdef MINIMALIST_PRINT
	printf("Creating scenario %d\r\n", mScenarioID);
#endif
	ScenarioID = mScenarioID;
	ScenarioName = mScenarioName;
	DeviceId = deviceId;
	Enabled = enabled;
	LastUpdated = lastUpdated;
	
	TaskList = new UTask*[MAX_TASK_NUMBER];

	for(int i = 0; i < MAX_TASK_NUMBER; i++)
	{
		TaskList[i] = NULL;
	}

	TaskCount = 0;
}


UScenario::~UScenario()
{
	for(int i = 0; i < MAX_TASK_NUMBER; i++)
	{
		delete [] TaskList[i];
	}
	delete [] TaskList;
}


int UScenario::AddTask(UTask *mTask)
{
	int retVal = 0;

	if (TaskCount < MAX_TASK_NUMBER)
	{
		TaskList[TaskCount++] = mTask;
		retVal = 1;
	}
	return retVal;
}


void UScenario::DelTask(int mTaskID)
{
	for (int i = 0; i < MAX_TASK_NUMBER; i++)
	{
		if (TaskList[i]->TaskID == mTaskID)
		{
			delete TaskList[i];
			for (int j = i; j < MAX_TASK_NUMBER - 1; j++)
			{
				TaskList[j] = TaskList[j+1];
			}
			TaskList[MAX_TASK_NUMBER] = NULL;
			
			TaskCount--;

			break;
		}
	}
}


int UScenario::DoTask(int device)
{
	if(!Enabled) 
	{
		return 0;
	}
	int i = 0;

	for (; i < TaskCount; i++)
	{
		if (TaskList[i]->CheckCondition(device))
		{
			TaskList[i]->SetValue();
		}
	}

	return 0;
}

void UScenario::GetJSON(char* returnValue)
{
	strcpy(returnValue, "{\"id\":\"");

	char buf[10];
	sprintf(buf, "%d", ScenarioID);
	strcat(returnValue, buf);
	
	strcat(returnValue, "\", \"name\":\"");

	strcat(returnValue, ScenarioName.c_str());
	
	strcat(returnValue, "\", \"enabled\":");
	if(Enabled)
		strcat(returnValue, "true");
	else
		strcat(returnValue, "false");

	strcat(returnValue, ", \"lastUpdated\":");
	char buf7[12];
	sprintf(buf7, "%d", LastUpdated);
	strcat(returnValue, buf7);
	
	strcat(returnValue, "}\0");
}



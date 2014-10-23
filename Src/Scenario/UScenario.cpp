#include "UScenario.h"
#include "UTask.h"

UScenario::UScenario()
{
	ScenarioID = 0;
	TaskCount = 0;

	for(int i = 0; i < MAX_TASK_NUMBER; i++)
	{
		TaskList[i] = NULL;
	}
}

UScenario::UScenario(int mScenarioID, char* mScenarioName)
{
	ScenarioID = mScenarioID;
	ScenarioName = mScenarioName;

	for(int i = 0; i < MAX_TASK_NUMBER; i++)
	{
		TaskList[i] = NULL;
	}

	TaskCount = 0;
}


UScenario::~UScenario()
{
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
	int i = 0;
	
	for (; i < MAX_TASK_NUMBER; i++)
	{
		if (TaskList[i]->TaskID == mTaskID)
		{
			int j = i;

			delete TaskList[i];
			for (; j < MAX_TASK_NUMBER - 1; j++)
			{
				if (TaskList[j + 1] != 0)
				{
					TaskList[j] = TaskList[j + 1];
				}
				else
				{
					break;
				}
			}
			delete TaskList[MAX_TASK_NUMBER - 1];
			TaskList[MAX_TASK_NUMBER - 1] = new UTask;
			TaskCount--;

			break;
		}
	}
}


int UScenario::DoTask(int device, int value)
{
	int i = 0;

	for (; i < TaskCount; i++)
	{
		if (TaskList[i]->CheckCondition(device, value))
		{
			TaskList[i]->SetValue();
		}
	}

	return 0;
}

char* UScenario::GetJSON()
{
	//"{\"id\":" + ScenarioID + ", \"name\":\"" + ScenarioName + "\"}";
	// {"id": + ScenarioID + , "name":" + ScenarioName + "}
	//     6        8           10            10         2

	//SCENARIO_NAME_LENGHT -> 8
	//ScenarioID (32 bits = 4,294,967,296) -> 10

	//Max length = 36

	char JSON[100] = {0};
	strcpy(JSON, "{\"id\":");

	char buf[10];
	sprintf(buf, "%d", ScenarioID);

	strcat(JSON, buf);
	strcat(JSON, ", \"name\":\"");

	//char buf2[10];
	//char* buf; ScenarioName

	printf("%s", ScenarioName);

	//strcat(JSON, p1);
	strcat(JSON, ScenarioName);
	strcat(JSON, "\"}");

	return JSON;
}


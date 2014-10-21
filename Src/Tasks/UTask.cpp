#include "UTask.h"


UTask::UTask()
{
	TaskID = 0;
	for(int i = 0; i < TASK_NAME_LENGHT; i++)
	{
		TaskName[i] = 0;
	}
	ConditionListIndex = 0;
}

UTask::UTask(int mTaskID, char mTaskName[TASK_NAME_LENGHT], int mActionValue, int mDeviceID)
{
	TaskID = mTaskID;
	DeviceID = mDeviceID;
	for(int i = 0; i < TASK_NAME_LENGHT; i++)
	{
		TaskName[i] = mTaskName[i];
	}
	ConditionListIndex = 0;
	ActionValue = mActionValue;
}


UTask::~UTask()
{
}


int UTask::AddCondition(UCondition *mCondition)
{
	int retVal = 0;
	if (mCondition)
	{
		if (ConditionListIndex < MAX_CONDITION_NUMBER)
		{
			ConditionList[ConditionListIndex++] = mCondition;
			retVal = 1;
		}
	}

	return retVal;
}


void UTask::DelCondition(int mCondtionID)
{
	int i = 0;

	for (; i < MAX_CONDITION_NUMBER; i++)
	{
		if (ConditionList[i]->ConditionID == mCondtionID)
		{
			int j = i;

			delete ConditionList[i];
			for (; j < MAX_CONDITION_NUMBER - 1; j++)
			{
				if (ConditionList[j + 1] != 0)
				{
					ConditionList[j] = ConditionList[j + 1];
				}
				else
				{
					break;
				}
			}
			ConditionList[MAX_CONDITION_NUMBER - 1] = new UCondition;
			ConditionListIndex--;

			break;
		}
	}
}


int UTask::CheckCondition()
{
	int RetVal = 1;

	for (int i = 0; i < ConditionListIndex; i++)
	{
		RetVal &= ConditionList[i]->CheckCondition();
	}

	return RetVal;
}


void UTask::SetValue()
{
#ifdef DEBUG_PRINT
	printf("Set actuator %lu value to %lu \n\r", DeviceID, ActionValue);
#endif
}

char* UTask::GetJSON()
{
	char JSON[100] = {0};

	strcpy(JSON, "{\"id\":");
	char buf1[10];
	sprintf(buf1, "%d", TaskID);
	strcat(JSON, buf1);

	strcat(JSON, "{, \"name\":\"");
	strcat(JSON, TaskName);

	strcat(JSON, "\", \"deviceId\":");
	char buf2[10];
	sprintf(buf2, "%d", DeviceID);
	strcat(JSON, buf2);

	strcat(JSON, "{\"actionValue\":");
	char buf3[10];
	sprintf(buf3, "%d", ActionValue);
	strcat(JSON, buf3);

	strcat(JSON, "}");

	return JSON;
}

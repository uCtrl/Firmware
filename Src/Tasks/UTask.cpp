#include "UTask.h"


UTask::UTask()
{
	TaskID = 0;
	ConditionListIndex = 0;

	for(int i = 0; i < MAX_CONDITION_NUMBER; i++)
	{
		ConditionList[i] = NULL;
	}
}

UTask::UTask(int mTaskID, char* mTaskName, int mActionValue, int mDeviceID)
{
	TaskID = mTaskID;
	DeviceID = mDeviceID;
	TaskName = mTaskName;

	for(int i = 0; i < MAX_CONDITION_NUMBER; i++)
	{
		ConditionList[i] = NULL;
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
//#ifdef DEBUG_PRINT
	printf("Set actuator %lu value to %lu \n\r", DeviceID, ActionValue);
//#endif
	DeviceHandler->SetActuatorValue(DeviceID, ActionValue);
}

char* UTask::GetJSON()
{
	char JSON[100] = {0};

	strcpy(JSON, "{\"id\":");
	char buf1[10];
	sprintf(buf1, "%d", TaskID);
	strcat(JSON, buf1);

	strcat(JSON, ", \"name\":\"");
	strcat(JSON, TaskName);

	strcat(JSON, "\", \"deviceId\":");
	char buf2[10];
	sprintf(buf2, "%d", DeviceID);
	strcat(JSON, buf2);

	strcat(JSON, ", \"actionValue\":");
	char buf3[10];
	sprintf(buf3, "%d", ActionValue);
	strcat(JSON, buf3);

	strcat(JSON, "}");

	return JSON;
}

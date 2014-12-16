#include "UTask.h"

extern Serial usbSerial;

UTask::UTask()
{
	TaskID = 0;
	ConditionListIndex = 0;

	for(int i = 0; i < MAX_CONDITION_NUMBER; i++)
	{
		ConditionList[i] = NULL;
	}
}

UTask::UTask(int mTaskID, bool enabled, int lastUpdated, string mActionValue)
{
#ifdef MINIMALIST_PRINT
	printf("Creating task %d\r\n", mTaskID);
#endif
	TaskID = mTaskID;
	DeviceID = -1; //mDeviceID;
	//TaskName = mTaskName;
	Enabled = enabled;
	LastUpdated = lastUpdated;
	
	ConditionList = new UCondition*[MAX_CONDITION_NUMBER];

	for(int i = 0; i < MAX_CONDITION_NUMBER; i++)
	{
		ConditionList[i] = NULL;
	}

	ConditionListIndex = 0;
	ActionValue = mActionValue;
}


UTask::~UTask()
{
	for(int i = 0; i < MAX_CONDITION_NUMBER; i++)
	{
		delete [] ConditionList[i];
	}
	delete [] ConditionList;
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


void UTask::DelCondition(int mConditionID)
{
	for (int i = 0; i < MAX_CONDITION_NUMBER; i++)
	{
		if (ConditionList[i]->ConditionId == mConditionID)
		{
			delete ConditionList[i];
			for (int j = i; j < MAX_CONDITION_NUMBER - 1; j++)
			{
				ConditionList[j] = ConditionList[j+1];
			}
			ConditionList[MAX_CONDITION_NUMBER] = NULL;
			
			ConditionListIndex--;

			break;
		}
	}
}


int UTask::CheckCondition(int device)
{
	if(!Enabled) 
	{
		return 0;
	}
	if(ConditionListIndex == 0) {
		return false;
	}
	else
	{
		int RetVal = 1;

#ifdef DEBUG_CONDITIONS
		printf("Task id %d\r\n", TaskID);
#endif
		for (int i = 0; i < ConditionListIndex; i++)
		{
			int conditionValue = 
			RetVal &= ConditionList[i]->CheckCondition(device);
#ifdef DEBUG_CONDITIONS
			printf("Condition value %d\r\n", conditionValue);
			printf("RetVal value %d\r\n", RetVal);
#endif
		}

		return RetVal;
	}
}


void UTask::SetValue()
{
#ifdef DEBUG_PRINT
	usbSerial.printf("Set actuator %lu value to %s \n\r", DeviceID, ActionValue.c_str());
#endif
	DeviceHandler->SetActuatorValue(DeviceID, ActionValue);
}

void UTask::GetJSON(char* returnValue)
{
	strcpy(returnValue, "{\"id\":\"");
	char buf1[10];
	sprintf(buf1, "%d", TaskID);
	strcat(returnValue, buf1);

	strcat(returnValue, "\", \"value\":\"");
	strcat(returnValue, ActionValue.c_str());
	
	strcat(returnValue, "\", \"enabled\":");
	if(Enabled)
		strcat(returnValue, "true");
	else
		strcat(returnValue, "false");

	strcat(returnValue, ", \"lastUpdated\":");
	char buf7[12];
	sprintf(buf7, "%d", LastUpdated);
	
	strcat(returnValue, buf7);
	strcat(returnValue, "}");
}


#include "UTask.h"


UTask::UTask()
{
	TaskID = 0;
	for(uint8_t i = 0; i < TASK_NAME_LENGHT; i++)
	{
		TaskName[i] = 0;
	}
	ConditionListIndex = 0;
}

UTask::UTask(uint32_t mTaskID, char mTaskName[TASK_NAME_LENGHT], uint32_t mActionValue, uint32_t mDeviceID)
{
	TaskID = mTaskID;
	DeviceID = mDeviceID;
	for(uint8_t i = 0; i < TASK_NAME_LENGHT; i++)
	{
		TaskName[i] = mTaskName[i];
	}
	ConditionListIndex = 0;
	ActionValue = mActionValue;
}


UTask::~UTask()
{
}


uint8_t UTask::AddCondition(UCondition *mCondition)
{
	uint8_t retVal = 0;
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


void UTask::DelCondition(uint32_t mCondtionID)
{
	uint32_t i = 0;

	for (; i < MAX_CONDITION_NUMBER; i++)
	{
		if (ConditionList[i]->ConditionID == mCondtionID)
		{
			uint32_t j = i;

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


uint32_t UTask::CheckCondition()
{
	uint32_t RetVal = 1;

	for (uint32_t i = 0; i < ConditionListIndex; i++)
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

#include "UTask.h"


UTask::UTask()
{
	TaskID = 0;
	for(uint8_t i = 0; i < TASK_NAME_LENGHT; i++)
	{
		TaskName[i] = 0;
	}
	ConditionListIndex = 0;
	ActionListIndex = 0;
}

UTask::UTask(uint32_t mTaskID, uint8_t mTaskName[TASK_NAME_LENGHT]) //uint8_t* mTaskName
{
	TaskID = mTaskID;
	for(uint8_t i = 0; i < TASK_NAME_LENGHT; i++)
	{
		TaskName[i] = mTaskName[i];
	}
	ConditionListIndex = 0;
	ActionListIndex = 0;
}


UTask::~UTask()
{
}


uint32_t UTask::AddCondition(UCondition *mCondition)
{
	if (mCondition)
	{
		if (ConditionListIndex < MAX_CONDITION_NUMBER)
		{
			ConditionList[ConditionListIndex++] = mCondition;
		}
	}

	return 0;
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


uint32_t UTask::AddAction(UAction *mAction)
{
	if (mAction)
	{
		if (ActionListIndex < MAX_ACTION_NUMBER)
		{
			ActionList[ActionListIndex++] = mAction;
		}
	}

	return 0;
}


void UTask::DelAction(uint32_t mActionID)
{
	uint32_t i = 0;

	for (; i < MAX_ACTION_NUMBER; i++)
	{
		if (ActionList[i]->ActionID == mActionID)
		{
			uint32_t j = i;

			delete ActionList[i];
			for (; j < MAX_ACTION_NUMBER - 1; j++)
			{
				if (ActionList[j + 1] != 0)
				{
					ActionList[j] = ActionList[j + 1];
				}
				else
				{
					break;
				}
			}
			ActionList[MAX_ACTION_NUMBER - 1] = new UAction;
			ActionListIndex--;

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


uint32_t UTask::DoAction()
{
	for (uint32_t i = 0; i < ActionListIndex; i++)
	{
		ActionList[i]->SetValue();
	}

	return 0;
}

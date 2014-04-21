#include "UScenery.h"

UScenery::UScenery()
{
	SceneryID = 0;
	for(uint8_t i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		SceneryName[i] = 0;
	}
	TaskListIndex = 0;
}

UScenery::UScenery(uint32_t mSceneryID, uint8_t mSceneryName[10])
{
	SceneryID = mSceneryID;

	for(uint8_t i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		SceneryName[i] = mSceneryName[i];
	}

	TaskListIndex = 0;
}


UScenery::~UScenery()
{
}


uint8_t UScenery::AddTask(UTask *mTask)
{
	uint8_t retVal = 0;

	if (TaskListIndex < MAX_TASK_NUMBER)
	{
		TaskList[TaskListIndex++] = mTask;
		retVal = 1;
	}
	return retVal;
}


void UScenery::DelTask(uint32_t mTaskID)
{
	uint32_t i = 0;
	
	for (; i < MAX_TASK_NUMBER; i++)
	{
		if (TaskList[i]->TaskID == mTaskID)
		{
			uint32_t j = i;

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
			TaskListIndex--;

			break;
		}
	}
}


uint32_t UScenery::DoTask()
{
	uint32_t i = 0;

	for (; i < TaskListIndex; i++)
	{
		if (TaskList[i]->CheckCondition())
		{
			TaskList[i]->SetValue();
		}
	}

	return 0;
}

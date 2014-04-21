#include "UScenery.h"

UScenery::UScenery()
{
	SceneryID = 0;
	for(uint8_t i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		SceneryName[i] = 0;
	}
	ListIndex = 0;
}

UScenery::UScenery(uint32_t mSceneryID, uint8_t mSceneryName[10])
{
	SceneryID = mSceneryID;

	for(uint8_t i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		SceneryName[i] = mSceneryName[i];
	}

	ListIndex = 0;
}


UScenery::~UScenery()
{
}


uint32_t UScenery::AddTask(UTask *mTask)
{
	if (ListIndex < MAX_TASK_NUMBER)
	{
		TaskList[ListIndex++] = mTask;
	}
	return 0;
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
			TaskList[MAX_TASK_NUMBER - 1] = new UTask;
			ListIndex--;

			break;
		}
	}
}


uint32_t UScenery::DoTask()
{
	uint32_t i = 0;

	for (; i < ListIndex; i++)
	{		
		if (TaskList[i]->TaskID != 0)
		{
			if (TaskList[i]->CheckCondition())
			{
				TaskList[i]->DoAction();
			}
		}
	}

	return 0;
}

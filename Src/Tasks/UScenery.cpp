#include "UScenery.h"

UScenery::UScenery()
{
	SceneryID = 0;
	for(int i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		SceneryName[i] = 0;
	}
	TaskListIndex = 0;
}

UScenery::UScenery(int mSceneryID, char mSceneryName[SCENERY_NAME_LENGHT])
{
	SceneryID = mSceneryID;

	for(int i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		SceneryName[i] = mSceneryName[i];
	}

	TaskListIndex = 0;
}


UScenery::~UScenery()
{
}


int UScenery::AddTask(UTask *mTask)
{
	int retVal = 0;

	if (TaskListIndex < MAX_TASK_NUMBER)
	{
		TaskList[TaskListIndex++] = mTask;
		retVal = 1;
	}
	return retVal;
}


void UScenery::DelTask(int mTaskID)
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
			TaskListIndex--;

			break;
		}
	}
}


int UScenery::DoTask()
{
	int i = 0;

	for (; i < TaskListIndex; i++)
	{
		if (TaskList[i]->CheckCondition())
		{
			TaskList[i]->SetValue();
		}
	}

	return 0;
}

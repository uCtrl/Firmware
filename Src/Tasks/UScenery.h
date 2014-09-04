#ifndef USCENERY_H_
#define USCENERY_H_

#include "UTask.h"
#include <stdint.h>
#include <stdio.h>
#include "TaskHandlerConfigFile.h"

class UScenery
{
public:
	UScenery();
	UScenery(int mSceneryID, char mSceneryName[SCENERY_NAME_LENGHT]);
	~UScenery();
	int AddTask(UTask *mTask);
	void DelTask(int mTaskID);
	int DoTask();

	int SceneryID;
	char SceneryName[SCENERY_NAME_LENGHT];
	UTask *TaskList[MAX_TASK_NUMBER];
	int TaskListIndex;
};

#endif // USCENERY_H_


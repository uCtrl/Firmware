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
	UScenery(uint32_t mSceneryID, char mSceneryName[SCENERY_NAME_LENGHT]);
	~UScenery();
	uint8_t AddTask(UTask *mTask);
	void DelTask(uint32_t mTaskID);
	uint32_t DoTask();

	uint32_t SceneryID;
	char SceneryName[SCENERY_NAME_LENGHT];
	UTask *TaskList[MAX_TASK_NUMBER];
	uint32_t TaskListIndex;
};

#endif // USCENERY_H_


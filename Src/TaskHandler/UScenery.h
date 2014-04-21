#ifndef USCENERY_H_
#define USCENERY_H_

#include "UTask.h"
#include "UCondition.h"
#include "UAction.h"
#include <stdint.h>
#include "TaskHandlerConfigFile.h"

class UScenery
{
public:
	UScenery();
	UScenery(uint32_t mSceneryID, uint8_t mSceneryName[SCENERY_NAME_LENGHT]);
	~UScenery();
	uint32_t AddTask(UTask *mTask);
	void DelTask(uint32_t mTaskID);
	uint32_t DoTask();

	uint32_t SceneryID;
	uint8_t SceneryName[SCENERY_NAME_LENGHT];
	UTask *TaskList[MAX_TASK_NUMBER];
	uint32_t ListIndex;
};

#endif // USCENERY_H_


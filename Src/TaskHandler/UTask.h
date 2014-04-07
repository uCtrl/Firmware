#ifndef UTASK_H_
#define UTASK_H_

#include "UCondition.h"
#include "UAction.h"
#include <stdint.h>
#include "TaskHandlerConfigFile.h"

class UTask
{
public:
	UTask();
	UTask(uint32_t mTaskID, uint8_t mTaskName[TASK_NAME_LENGHT]);
	~UTask();
	uint32_t AddCondition(UCondition *mCondition);
	void DelCondition(uint32_t mCondtionID);
	uint32_t AddAction(UAction *mAction);
	void DelAction(uint32_t mActionID);
	uint32_t CheckCondition();
	uint32_t DoAction();

	uint32_t TaskID;
	uint8_t TaskName[10];
	UCondition *ConditionList[MAX_CONDITION_NUMBER];
	uint32_t ConditionListIndex;
	UAction *ActionList[MAX_ACTION_NUMBER];
	uint32_t ActionListIndex;
};

#endif // UTASK_H_

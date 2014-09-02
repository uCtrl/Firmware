#ifndef UTASK_H_
#define UTASK_H_

#include "UCondition.h"
#include <stdint.h>
#include <stdio.h>
#include "TaskHandlerConfigFile.h"

class UTask
{
public:
	UTask();
	UTask(uint32_t mTaskID, char mTaskName[TASK_NAME_LENGHT], uint32_t mActionValue, uint32_t mDeviceID);
	~UTask();
	uint8_t AddCondition(UCondition *mCondition);
	void DelCondition(uint32_t mCondtionID);
	uint32_t CheckCondition();
	void SetValue();

	uint32_t TaskID;
	uint32_t DeviceID;
	char TaskName[TASK_NAME_LENGHT];
	UCondition *ConditionList[MAX_CONDITION_NUMBER];
	uint32_t ConditionListIndex;
	uint32_t ActionValue;
};

#endif // UTASK_H_

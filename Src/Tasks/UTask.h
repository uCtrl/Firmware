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
	UTask(int mTaskID, char mTaskName[TASK_NAME_LENGHT], int mActionValue, int mDeviceID);
	~UTask();
	int AddCondition(UCondition *mCondition);
	void DelCondition(int mCondtionID);
	int CheckCondition();
	void SetValue();

	int TaskID;
	int DeviceID;
	char TaskName[TASK_NAME_LENGHT];
	UCondition *ConditionList[MAX_CONDITION_NUMBER];
	int ConditionListIndex;
	int ActionValue;
};

#endif // UTASK_H_

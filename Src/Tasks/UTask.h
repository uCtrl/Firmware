#ifndef UTASK_H_
#define UTASK_H_

#include "mbed.h"
#include "UCondition.h"
#include <stdint.h>
#include <stdio.h>
#include "TaskHandlerConfigFile.h"
//#include "UDeviceHandler.h"

class UDeviceHandler;

class UTask
{
public:
	UTask();
	UTask(int mTaskID, char* mTaskName, int mActionValue, int mDeviceID);
	~UTask();
	int AddCondition(UCondition *mCondition);
	void DelCondition(int mCondtionID);
	int CheckCondition(int device, int value);
	void SetValue();
	char* GetJSON();

	int TaskID;
	int DeviceID;
	char* TaskName;
	UCondition *ConditionList[MAX_CONDITION_NUMBER];
	int ConditionListIndex;
	int ActionValue;
	UDeviceHandler* DeviceHandler;
};

#endif // UTASK_H_

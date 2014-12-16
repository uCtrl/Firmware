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
	UTask(int mTaskID, bool enabled, int lastUpdated, string mActionValue);
	~UTask();
	int AddCondition(UCondition *mCondition);
	void DelCondition(int mCondtionID);
	int CheckCondition(int device);
	void SetValue();
	void GetJSON(char* returnValue);

	int TaskID;
	int DeviceID;
	//char* TaskName;
	UCondition** ConditionList;
	int ConditionListIndex;
	string ActionValue;
	UDeviceHandler* DeviceHandler;
	bool Enabled;
	int LastUpdated;
};

#endif // UTASK_H_


#ifndef UScenario_H_
#define UScenario_H_

#include "mbed.h"
//#include "UTask.h"
#include <stdint.h>
#include <stdio.h>
#include <string>
#include "TaskHandlerConfigFile.h"

class UTask;

class UScenario
{
public:
	UScenario();
	UScenario(int mScenarioID, string mScenarioName, bool enabled, int lastUpdated, int deviceId);
	~UScenario();
	int AddTask(UTask *mTask);
	void DelTask(int mTaskID);
	int DoTask(int device);
	void GetJSON(char* returnValue);

	int ScenarioID;
	string ScenarioName;
	UTask** TaskList;
	int TaskCount;
	int DeviceId;
	bool Enabled;
	int LastUpdated;
};

#endif // UScenario_H_



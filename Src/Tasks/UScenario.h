#ifndef UScenario_H_
#define UScenario_H_

#include "mbed.h"
#include "UTask.h"
#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "TaskHandlerConfigFile.h"

class UScenario
{
public:
	UScenario();
	UScenario(int mScenarioID, char mScenarioName[SCENARIO_NAME_LENGHT]);
	~UScenario();
	int AddTask(UTask *mTask);
	void DelTask(int mTaskID);
	int DoTask();
	char* GetJSON();

	int ScenarioID;
	char ScenarioName[SCENARIO_NAME_LENGHT];
	UTask *TaskList[MAX_TASK_NUMBER];
	int TaskCount;
};

#endif // UScenario_H_


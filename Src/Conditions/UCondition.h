#ifndef UCONDITION_H_
#define UCONDITION_H_

#include "UOperatorType.h"
#include "TaskHandlerConfigFile.h"
#include <stdint.h>
#include "UEvent.h"

extern UTaskEvent EventPool[];
extern int EventPoolIndex;

class UCondition
{
public:

	UCondition();
	UCondition(int mConditionID, int mSensorID, int mValue, UOperatorType mConditionOperator, char mConditionName[CONDITION_NAME_LENGHT]);
	virtual ~UCondition();
	virtual int CheckCondition();
	int GetSensorValue(int mSensorID);

	int ConditionID;
	int SensorID;
	int Value;
	UOperatorType ConditionOperator;
	char ConditionName[CONDITION_NAME_LENGHT];

};

#endif // UCONDITION_H_

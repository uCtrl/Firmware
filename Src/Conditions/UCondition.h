#ifndef UCONDITION_H_
#define UCONDITION_H_

#include "mbed.h"
#include "UOperatorType.h"
#include "TaskHandlerConfigFile.h"
#include <stdint.h>
#include "UEvent.h"
#include "USensor.h"
#include "UDeviceHandler.h"

extern UTaskEvent EventPool[];
extern int EventPoolIndex;

class UDeviceHandler;

class UCondition
{
public:

	UCondition();
	UCondition(int mConditionID, char* mConditionName, int mSensorID, int mValue, UOperatorType mConditionOperator);
	virtual ~UCondition();
	virtual int CheckCondition(int device, int value);
	int GetSensorValue(int mSensorID);
	char* GetJSON();

	int ConditionID;
	int SensorID;
	int Value;
	UOperatorType ConditionOperator;
	char* ConditionName;
	UDeviceHandler* DeviceHandler;

};

#endif // UCONDITION_H_

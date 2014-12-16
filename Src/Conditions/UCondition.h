#ifndef UCONDITION_H_
#define UCONDITION_H_

#include "mbed.h"
#include "UComparisonType.h"
#include "TaskHandlerConfigFile.h"
#include <stdint.h>
#include "UTaskEvent.h"
#include "USensor.h"
#include "UDeviceHandler.h"
#include "UConditionType.h"

extern UTaskEvent EventPool[];
extern int EventPoolIndex;

class UDeviceHandler;

class UCondition
{
public:

	UCondition();
	UCondition(int conditionId, UConditionType conditionType,  UComparisonType comparisonType, int beginValue, int endValue, int deviceId, bool enabled, int lastUpdated);
	virtual ~UCondition();
	virtual int CheckCondition(int a_device);
	void UpdateSensorValue(int a_value);
	void GetJSON(char* returnValue);

	int ConditionId;
	UConditionType ConditionType;
	UComparisonType ComparisonType;
	int EndValue;
	int BeginValue;
	int DeviceId;
	bool Enabled;
	int LastUpdated;
	
	UDeviceHandler* DeviceHandler;
	int LastSensorValue;
	int LastConditionValue;

private:
	int GetValueToCompareTo();
	
	bool IsInBetween(int a_value, int a_low, int a_high);
};

#endif // UCONDITION_H_


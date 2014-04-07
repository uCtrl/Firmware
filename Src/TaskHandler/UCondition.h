#ifndef UCONDITION_H_
#define UCONDITION_H_

#include "UOperatorType.h"
#include <stdint.h>
#include "TaskHandlerConfigFile.h"

class UCondition
{
public:

	UCondition();
	UCondition(uint32_t mConditionID, uint32_t mSensorID, uint32_t mValue, UOperatorType mConditionOperator, uint8_t mConditionName[CONDITION_NAME_LENGHT]);
	virtual ~UCondition();
	virtual uint32_t CheckCondition();
	uint32_t GetSensorValue(uint32_t mSensorID);

	uint32_t ConditionID;
	uint32_t SensorID;
	uint32_t Value;
	UOperatorType ConditionOperator;
	uint8_t ConditionName[CONDITION_NAME_LENGHT];

};

#endif // UCONDITION_H_

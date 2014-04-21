#include "UCondition.h"


UCondition::UCondition()
{
	ConditionID = 0;
	for(uint8_t i = 0; i < CONDITION_NAME_LENGHT; i++)
	{
		ConditionName[i] = 0;
	}
	SensorID = 0;
	Value = 0;
	ConditionOperator = OPERATOR_TYPE_NONE;
}

UCondition::UCondition(uint32_t mConditionID, uint32_t mSensorID, uint32_t mValue, UOperatorType mConditionOperator, uint8_t mConditionName[CONDITION_NAME_LENGHT])
{
	ConditionID = mConditionID;
	SensorID = mSensorID;
	Value = mValue;
	ConditionOperator = mConditionOperator;
	for(uint8_t i = 0; i < CONDITION_NAME_LENGHT; i++)
	{
		ConditionName[i] = mConditionName[i];
	}
}

UCondition::~UCondition()
{
}


uint32_t UCondition::CheckCondition()
{
	uint32_t retVal = 0;
	uint32_t sensorValue = GetSensorValue(SensorID);

	switch(ConditionOperator)
	{
	case LESSER:
		if(sensorValue < Value)
		{
			retVal = 1;
		}
		break;
	case LESSER_EQUAL:
		if(sensorValue <= Value)
		{
			retVal = 1;
		}
		break;
	case GREATER:
		if(sensorValue > Value)
		{
			retVal = 1;
		}
		break;
	case GREATER_EQUAL:
		if(sensorValue <= Value)
		{
			retVal = 1;
		}
		break;
	case EQUAL:
		if(sensorValue == Value)
		{
			retVal = 1;
		}
		break;
	case NOT_EQUAL:
		if(sensorValue != Value)
		{
			retVal = 1;
		}
		break;
	case OPERATOR_TYPE_NONE:
		break;
	}

	return retVal;
}

uint32_t UCondition::GetSensorValue(uint32_t mSensorID)
{
	uint32_t value = 0;

	for(uint32_t i = 0; i < EventPoolIndex; i++)
	{
		if(EventPool[i].sensorId == mSensorID)
		{
			value = EventPool[i].value;
		}
	}

	return value;
}

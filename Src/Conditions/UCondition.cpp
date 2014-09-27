#include "UCondition.h"


UCondition::UCondition()
{
	ConditionID = 0;
	for(int i = 0; i < CONDITION_NAME_LENGHT; i++)
	{
		ConditionName[i] = 0;
	}
	SensorID = 0;
	Value = 0;
	ConditionOperator = OPERATOR_TYPE_NONE;
}

UCondition::UCondition(int mConditionID, int mSensorID, int mValue, UOperatorType mConditionOperator, char mConditionName[CONDITION_NAME_LENGHT])
{
	ConditionID = mConditionID;
	SensorID = mSensorID;
	Value = mValue;
	ConditionOperator = mConditionOperator;
	for(int i = 0; i < CONDITION_NAME_LENGHT; i++)
	{
		ConditionName[i] = mConditionName[i];
	}
}

UCondition::~UCondition()
{
}


int UCondition::CheckCondition()
{
	int retVal = 0;
	int sensorValue = GetSensorValue(SensorID);

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

int UCondition::GetSensorValue(int mSensorID)
{
	int value = 0;

	for(int i = 0; i < EventPoolIndex; i++)
	{
		if(EventPool[i].sensorId == mSensorID)
		{
			value = EventPool[i].value;
		}
	}

	return value;
}

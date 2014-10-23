#include "UCondition.h"


UCondition::UCondition()
{
	ConditionID = 0;
	SensorID = 0;
	Value = 0;
	ConditionOperator = OPERATOR_TYPE_NONE;
}

UCondition::UCondition(int mConditionID, char* mConditionName, int mSensorID, int mValue, UOperatorType mConditionOperator)
{
	ConditionID = mConditionID;
	SensorID = mSensorID;
	Value = mValue;
	ConditionOperator = mConditionOperator;
	ConditionName = mConditionName;
}

UCondition::~UCondition()
{
}


int UCondition::CheckCondition()
{
	int retVal = 0;
	USensor* sensor = DeviceHandler->GetSensor(SensorID);
	int sensorValue = sensor->ReadValue(); //UDeviceHandler->;

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

char* UCondition::GetJSON()
{
	char JSON[100] = {0};

	strcpy(JSON, "{\"id\":");
	char buf1[10];
	sprintf(buf1, "%d", ConditionID);
	strcat(JSON, buf1);

	strcat(JSON, ", \"name\":\"");
	strcat(JSON, ConditionName);

	strcat(JSON, "\", \"deviceId\":");
	char buf2[10];
	sprintf(buf2, "%d", SensorID);
	strcat(JSON, buf2);

	strcat(JSON, ", \"value\":");
	char buf3[10];
	sprintf(buf3, "%d", Value);
	strcat(JSON, buf3);

	strcat(JSON, ", \"conditionOperator\":");
	char buf4[10];
	sprintf(buf4, "%d", ConditionOperator);
	strcat(JSON, buf4);

	strcat(JSON, "}");

	return JSON;
}

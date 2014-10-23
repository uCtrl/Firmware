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


int UCondition::CheckCondition(int device, int value)
{
	int retVal = 0;

#ifdef DEBUG_PRINT
	printf("Checking condition...");
#endif

	if(device == SensorID) {
		int sensorValue = value;

		switch(ConditionOperator)
		{
		case LESSER:
			if(sensorValue < Value)
			{
#ifdef DEBUG_PRINT
				printf("true! \r\n");
#endif
				retVal = 1;
			} else {
#ifdef DEBUG_PRINT
				printf("false! \r\n");
#endif
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
#ifdef DEBUG_PRINT
				printf("true! \r\n");
#endif
				retVal = 1;
			} else {
#ifdef DEBUG_PRINT
				printf("false! \r\n");
#endif
			}
			break;
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

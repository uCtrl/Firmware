#include "UCondition.h"

extern Serial usbSerial;

UCondition::UCondition()
{
	ConditionId = 0;
	ConditionType = UNDEFINED;
	ComparisonType = NONE;
	EndValue = 0;
	BeginValue = 0;
	DeviceId = 0;
	Enabled = false;
	LastUpdated = 0;
}

UCondition::UCondition(int conditionId, UConditionType conditionType,  UComparisonType comparisonType, int beginValue, int endValue, int deviceId, bool enabled, int lastUpdated)
{
#ifdef MINIMALIST_PRINT
	usbSerial.printf("Creating condition %d\r\n", conditionId);
#endif
	ConditionId = conditionId;
	ConditionType = conditionType;
	ComparisonType = comparisonType;
	EndValue = endValue;
	BeginValue = beginValue;
	DeviceId = deviceId;
	Enabled = enabled;
	LastUpdated = lastUpdated;
	LastConditionValue = 0;
}

UCondition::~UCondition()
{
}


int UCondition::CheckCondition(int device)
{
	if(!Enabled) 
	{
		return 0;
	}

	int valueToCompare = GetValueToCompareTo();

#ifdef DEBUG_CONDITIONS
	usbSerial.printf("Checking condition %d : value = %d, ", ConditionId, valueToCompare);
#endif
	
	int retVal = LastConditionValue;

	if((ConditionType == DEVICE && device == DeviceId) || ConditionType != DEVICE) 
	{
		switch(ComparisonType)
		{
		case NONE:
			retVal = 0;
			break;
			
		case GREATER_THAN:		
			if(valueToCompare > EndValue)
				retVal = 1;
			else
				retVal = 0;
			break;
			
		case LESSER_THAN:				
			if(valueToCompare < BeginValue)
				retVal = 1;
			else
				retVal = 0;
			break;
		case EQUAL:
		{
			switch(ConditionType)
			{
				case UNDEFINED:
					return 0;
				case DATE:		 	
					if(valueToCompare/86400 != BeginValue/86400)
						retVal = 1;
					else
						retVal = 0;
					break;
			    case DAY: 	
			    {
				    int m_sunday = 1, m_monday = 2, m_tuesday = 4, m_wendnesday = 8, m_thursday = 16, m_friday = 32, m_saturday = 64; 
				    const int sunday = 3, monday = 4, tuesday = 5, wendnesday = 6, thursday = 0, friday = 1, saturday = 2; 
				    int on_sunday = 0, on_monday = 0, on_tuesday = 0, on_wendnesday = 0, on_thursday = 0, on_friday = 0, on_saturday = 0;
				
				    int currentDay = valueToCompare/86400;
				    
				    if ((BeginValue & m_sunday) == m_sunday)
				    	on_sunday = 1;
				    if ((BeginValue & m_monday) == m_monday)
				    	on_monday = 1;
				    if ((BeginValue & m_tuesday) == m_tuesday)
				    	on_tuesday = 1;
				    if ((BeginValue & m_wendnesday) == m_wendnesday)
				    	on_wendnesday = 1;
				    if ((BeginValue & m_thursday) == m_thursday)
				    	on_thursday = 1;
				    if ((BeginValue & m_friday) == m_friday)
				    	on_friday = 1;
				    if ((BeginValue & m_saturday) == m_saturday)
				    	on_saturday = 1;
					
					switch (currentDay)
					{
						case thursday:
							if(on_thursday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
						case friday:
							if(on_friday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
						case saturday:
							if(on_saturday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
						case sunday:
							if(on_sunday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
						case monday:
							if(on_monday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
						case tuesday:
							if(on_tuesday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
						case wendnesday:
							if(on_wendnesday == 1)
								retVal = 1;
							else
								retVal = 0;
							break;
					}
  
					//usbSerial.printf("Mask : %d\r\n", BeginValue);
					//usbSerial.printf("Current day : %d is active? %d\r\n", currentDay, retVal);
					
					break;
					
				}
			    case TIME:   
					if(valueToCompare == BeginValue)
						retVal = 1;
					else
						retVal = 0;
					break;
			    case DEVICE:
			    	if(valueToCompare != BeginValue)
						retVal = 1;
					else
						retVal = 0;
					break;
			    default:
					return 0;
			}
			break;
	    }
		case IN_BETWEEN:
			if(BeginValue <= valueToCompare && valueToCompare <= EndValue)
				retVal = 1;
			else
				retVal = 0;
			break;
		case NOT:
			// Nothing ?
			retVal = 0;
			break;
		case NOT_GREATER_THAN:
			if(valueToCompare <= BeginValue)
				retVal = 1;
			else
				retVal = 0;
			break;
		case NOT_LESSER_THAN:
			if(valueToCompare >= BeginValue)
				retVal = 1;
			else
				retVal = 0;
			break;
		case NOT_EQUAL:
			switch(ConditionType)
			{
				case UNDEFINED:
					return 0;
				case DATE:		 	
					if(valueToCompare/86400 != BeginValue/86400)
						retVal = 1;
					else
						retVal = 0;
					break;
			    case DAY: 	
			    	//does not happen
					break;
			    case TIME:   
					if(valueToCompare/(24*60*60) != BeginValue/24*60*60)
						retVal = 1;
					else
						retVal = 0;
					break;
			    case DEVICE:
			    	if(valueToCompare != BeginValue)
						retVal = 1;
					else
						retVal = 0;
					break;
			    default:
					return 0;
			}
			break;
		case NOT_IN_BETWEEN:
			if(BeginValue <= valueToCompare && valueToCompare <= EndValue)
				retVal = 0;
			else
				retVal = 1;
			break;
		}
	}

#ifdef DEBUG_CONDITIONS
	if(retVal == 1)
		usbSerial.printf(" -> TRUE\r\n");
	if(retVal == 0)
		usbSerial.printf(" -> FALSE\r\n");
#endif

	LastConditionValue = retVal;
	return retVal;
}

void UCondition::UpdateSensorValue(int value)
{
#ifdef DEBUG_PRINT
	//printf("Updating condition %d (Sensor %d) value to : %d\r\n", ConditionID, ConditionId, value);
#endif
	LastSensorValue = value;
	LastUpdated = time(NULL);
}


int UCondition::GetValueToCompareTo()
{
	switch(ConditionType)
	{
		case UNDEFINED:
			return 0;
		case DATE:		 	
			return time(NULL) % 31556926;
	    case DAY: 	
	    	return time(NULL) % 604800;
	    case TIME:   
	    	return time(NULL) % 86400;
	    case DEVICE:
	    	return LastSensorValue;
	    default:
			return 0;
	}
}

void UCondition::GetJSON(char* returnValue)
{
	strcpy(returnValue, "{\"id\":\"");
	char buf1[10];
	sprintf(buf1, "%d", ConditionId);
	strcat(returnValue, buf1);
	
	strcat(returnValue, "\", \"type\":");
	char buf2[10];
	sprintf(buf2, "%d", ConditionType);
	strcat(returnValue, buf2);

	strcat(returnValue, ", \"comparisonType\":");
	char buf3[10];
	sprintf(buf3, "%d", ComparisonType);
	strcat(returnValue, buf3);
	
	strcat(returnValue, ", \"beginValue\":\"");
	char buf4[10];
	sprintf(buf4, "%d", BeginValue);
	strcat(returnValue, buf4);
	
	strcat(returnValue, "\", \"endValue\":\"");
	char buf5[10];
	sprintf(buf5, "%d", EndValue);
	strcat(returnValue, buf5);
	
	strcat(returnValue, "\", \"deviceId\":\"");
	char buf6[10];
	sprintf(buf6, "%d", DeviceId);
	strcat(returnValue, buf6);

	strcat(returnValue, "\", \"enabled\":");
	if(Enabled)
		strcat(returnValue, "true");
	else
		strcat(returnValue, "false");

	strcat(returnValue, ", \"lastUpdated\":");
	char buf7[12];
	sprintf(buf7, "%d", LastUpdated);
	strcat(returnValue, buf7);

	strcat(returnValue, "}\0");
}


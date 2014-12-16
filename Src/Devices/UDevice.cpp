#include "UDevice.h"
#include "UMathUtils.h"

extern Serial usbSerial;

UDevice::UDevice()
{
	DeviceID = 0;
	ScenarioCount = 0;
	CurrentValue = 0;

	for(int i = 0; i < MAX_SCENARIO_NUMBER; i++)
	{
		ScenarioList[i] = NULL;
	}
}

UDevice::UDevice(int mDeviceID, string mDeviceName, UDeviceType type, string description, string maxValue, string minValue, string value,
				 int precision, int status, string unitLabel, bool enabled, int lastUpdated)
{
#ifdef MINIMALIST_PRINT
	printf("Creating device %d\r\n", mDeviceID);
#endif
	DeviceID = mDeviceID;
	DeviceType = type;
	DeviceName = mDeviceName;
	CurrentValue = 0;

	ScenarioList = new UScenario*[MAX_SCENARIO_NUMBER];

	ScenarioCount = 0;
	for(int i = 0; i < MAX_SCENARIO_NUMBER; i++)
	{
		ScenarioList[i] = NULL;
	}
	
	Description = description;
	MaxValue = maxValue;
	MinValue = minValue;
	Value = value;
	Precision = precision;
	Status = status;
	UnitLabel = unitLabel;
	Enabled = enabled;
	LastUpdated = lastUpdated;
}


UDevice::~UDevice()
{			
	for(int i = 0; i < MAX_SCENARIO_NUMBER; i++)
	{
		delete [] ScenarioList[i];
	}
	delete [] ScenarioList;
}


bool UDevice::AddScenario(UScenario *mScenario)
{
	if (ScenarioCount < MAX_SCENARIO_NUMBER)
	{
		ScenarioList[ScenarioCount++] = mScenario;
		return true;
	}
	return false;
}


void UDevice::DelScenario(int mScenarioID)
{
	for (int i = 0; i < MAX_SCENARIO_NUMBER; i++)
	{
		if (ScenarioList[i]->ScenarioID == mScenarioID)
		{
			delete ScenarioList[i];
			for (int j = i; j < MAX_SCENARIO_NUMBER - 1; j++)
			{
				ScenarioList[j] = ScenarioList[j+1];
			}
			ScenarioList[MAX_SCENARIO_NUMBER] = NULL;
			
			ScenarioCount--;

			break;
		}
	}
}

// Returns how many scenarios were accomplished
int UDevice::DoScenario(int device)
{
	if(!Enabled) 
	{
		return 0;
	}
	
	int i = 0;

	for (; i < ScenarioCount; i++)
	{
#ifdef DEBUG_PRINT
		usbSerial.printf("Doing scenario of device : %d\r\n", DeviceID);
#endif
		ScenarioList[i]->DoTask(device);
	}

	return i;
}

void UDevice::GetJSON(char* returnValue)
{
	strcpy(returnValue, "{\"id\":\"");
	char buf1[10];
	sprintf(buf1, "%d", DeviceID);
	strcat(returnValue, buf1);

	strcat(returnValue, "\", \"name\":\"");
	strcat(returnValue, DeviceName.c_str());

	strcat(returnValue, "\", \"type\":");
	char buf2[10];
	sprintf(buf2, "%d", (int) DeviceType);
	strcat(returnValue, buf2);

	strcat(returnValue, ", \"description\":\"");
	strcat(returnValue, Description.c_str());
	
	strcat(returnValue, "\", \"maxValue\":\"");
	strcat(returnValue, MaxValue.c_str());
	
	strcat(returnValue, "\", \"minValue\":\"");
	strcat(returnValue, MinValue.c_str());
	
	strcat(returnValue, "\", \"value\":\"");
	char buf_val[10];
	
	switch(Precision)
	{
		case 1 :
			sprintf(buf_val, "%.1f", CurrentValue);
			break;	
		case 2 :
			sprintf(buf_val, "%.2f", CurrentValue);
			break;	
		case 3 :
			sprintf(buf_val, "%.3f", CurrentValue);
			break;	
		case 4 :
			sprintf(buf_val, "%.4f", CurrentValue);
			break;	
		case 5 :
			sprintf(buf_val, "%.5f", CurrentValue);
			break;	
		default:
			sprintf(buf_val, "%.0f", CurrentValue);
			break;	
	}
	
	strcat(returnValue, buf_val);
	
	strcat(returnValue, "\", \"precision\":");
	char buf3[10];
	sprintf(buf3, "%d", Precision);
	strcat(returnValue, buf3);
	
	strcat(returnValue, ", \"status\":");
	char buf4[10];
	sprintf(buf4, "%d", Status);
	strcat(returnValue, buf4);
	
	strcat(returnValue, ", \"unitLabel\":\"");
	strcat(returnValue, UnitLabel.c_str());
	
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


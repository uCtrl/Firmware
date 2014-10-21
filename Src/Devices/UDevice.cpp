#include "UDevice.h"

UDevice::UDevice()
{
	DeviceID = 0;

	/*
	for(int i = 0; i < SCENARIO_NAME_LENGHT; i++)
	{
		DeviceName[i] = 0;
	}*/
	ScenarioCount = 0;
}

UDevice::UDevice(int mDeviceID, char* mDeviceName/*[DEVICE_NAME_LENGHT]*/, UDeviceType type)
{
	DeviceID = mDeviceID;
	DeviceType = type;
	DeviceName = mDeviceName;
	/*
	for(int i = 0; i < DEVICE_NAME_LENGHT; i++)
	{
		DeviceName[i] = mDeviceName[i];
	}*/

	ScenarioCount = 0;
}


UDevice::~UDevice()
{
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
	int i = 0;

	for (; i < MAX_SCENARIO_NUMBER; i++)
	{
		if (ScenarioList[i]->ScenarioID == mScenarioID)
		{
			int j = i;

			delete ScenarioList[i];
			for (; j < MAX_SCENARIO_NUMBER - 1; j++)
			{
				if (ScenarioList[j + 1] != 0)
				{
					ScenarioList[j] = ScenarioList[j + 1];
				}
				else
				{
					break;
				}
			}
			delete ScenarioList[MAX_SCENARIO_NUMBER - 1];
			ScenarioList[MAX_SCENARIO_NUMBER - 1] = new UScenario;
			ScenarioCount--;

			break;
		}
	}
}

// Returns how many scenarios were accomplished
int UDevice::DoScenario()
{
	int i = 0;

	for (; i < ScenarioCount; i++)
	{
		ScenarioList[i]->DoTask();
	}

	return i;
}


char* UDevice::GetJSON()
{
	char JSON[100] = {0};

	strcpy(JSON, "{\"id\":");
	char buf1[10];
	sprintf(buf1, "%d", m_deviceID);
	strcat(JSON, buf1);

	strcat(JSON, ", \"name\":\"");
	strcat(JSON, DeviceName);

	printf("Device name: %s\r\n", (char*) DeviceName);

	strcat(JSON, "\", \"type\":");
	char buf2[10];
	sprintf(buf2, "%d", (int) DeviceType);
	strcat(JSON, buf2);

	strcat(JSON, "}");

	return JSON;
}

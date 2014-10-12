#include "UDevice.h"

UDevice::UDevice()
{
	DeviceID = 0;
	for(int i = 0; i < SCENARIO_NAME_LENGHT; i++)
	{
		DeviceName[i] = 0;
	}
	ScenarioListIndex = 0;
}

UDevice::UDevice(int mDeviceID, char mDeviceName[DEVICE_NAME_LENGHT])
{
	DeviceID = mDeviceID;

	for(int i = 0; i < SCENARIO_NAME_LENGHT; i++)
	{
		DeviceName[i] = mDeviceName[i];
	}

	ScenarioListIndex = 0;
}


UDevice::~UDevice()
{
}


bool UDevice::AddScenario(UScenario *mScenario)
{
	if (ScenarioListIndex < MAX_TASK_NUMBER)
	{
		ScenarioList[ScenarioListIndex++] = mScenario;
		return true;
	}
	return false;
}


void UDevice::DelScenario(int mScenarioID)
{
	int i = 0;

	for (; i < MAX_TASK_NUMBER; i++)
	{
		if (ScenarioList[i]->ScenarioID == mScenarioID)
		{
			int j = i;

			delete ScenarioList[i];
			for (; j < MAX_TASK_NUMBER - 1; j++)
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
			delete ScenarioList[MAX_TASK_NUMBER - 1];
			ScenarioList[MAX_TASK_NUMBER - 1] = new UScenario;
			ScenarioListIndex--;

			break;
		}
	}
}

// Returns how many scenarios were accomplished
int UDevice::DoScenario()
{
	int i = 0;

	for (; i < ScenarioListIndex; i++)
	{
		ScenarioList[i]->DoTask();
	}

	return i;
}

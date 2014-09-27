#include "UDevice.h"

UDevice::UDevice()
{
	DeviceID = 0;
	for(int i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		DeviceName[i] = 0;
	}
	SceneryListIndex = 0;
}

UDevice::UDevice(int mDeviceID, char mDeviceName[DEVICE_NAME_LENGHT])
{
	DeviceID = mDeviceID;

	for(int i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		DeviceName[i] = mDeviceName[i];
	}

	SceneryListIndex = 0;
}


UDevice::~UDevice()
{
}


bool UDevice::AddScenery(UScenery *mScenery)
{
	if (SceneryListIndex < MAX_TASK_NUMBER)
	{
		SceneryList[SceneryListIndex++] = mScenery;
		return true;
	}
	return false;
}


void UDevice::DelScenery(int mSceneryID)
{
	int i = 0;

	for (; i < MAX_TASK_NUMBER; i++)
	{
		if (SceneryList[i]->SceneryID == mSceneryID)
		{
			int j = i;

			delete SceneryList[i];
			for (; j < MAX_TASK_NUMBER - 1; j++)
			{
				if (SceneryList[j + 1] != 0)
				{
					SceneryList[j] = SceneryList[j + 1];
				}
				else
				{
					break;
				}
			}
			delete SceneryList[MAX_TASK_NUMBER - 1];
			SceneryList[MAX_TASK_NUMBER - 1] = new UScenery;
			SceneryListIndex--;

			break;
		}
	}
}

// Returns how many scenarios were accomplished
int UDevice::DoScenery()
{
	int i = 0;

	for (; i < SceneryListIndex; i++)
	{
		SceneryList[i]->DoTask();
	}

	return i;
}

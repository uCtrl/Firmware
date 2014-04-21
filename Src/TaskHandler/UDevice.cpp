#include "UDevice.h"

UDevice::UDevice()
{
	DeviceID = 0;
	for(uint8_t i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		DeviceName[i] = 0;
	}
	SceneryListIndex = 0;
}

UDevice::UDevice(uint32_t mSceneryID, uint8_t mSceneryName[10])
{
	DeviceID = mSceneryID;

	for(uint8_t i = 0; i < SCENERY_NAME_LENGHT; i++)
	{
		DeviceName[i] = mSceneryName[i];
	}

	SceneryListIndex = 0;
}


UDevice::~UDevice()
{
}


uint8_t UDevice::AddScenery(UScenery *mScenery)
{
	uint8_t retVal = 0;
	if (SceneryListIndex < MAX_TASK_NUMBER)
	{
		SceneryList[SceneryListIndex++] = mScenery;
		retVal = 1;
	}
	return retVal;
}


void UDevice::DelScenery(uint32_t mSceneryID)
{
	uint32_t i = 0;

	for (; i < MAX_TASK_NUMBER; i++)
	{
		if (SceneryList[i]->SceneryID == mSceneryID)
		{
			uint32_t j = i;

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


uint32_t UDevice::DoScenery()
{
	uint32_t i = 0;

	for (; i < SceneryListIndex; i++)
	{
		SceneryList[i]->DoTask();
	}

	return 0;
}

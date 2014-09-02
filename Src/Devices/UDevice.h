#ifndef UDEVICE_H_
#define UDEVICE_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"
#include "UScenery.h"

class UDevice
{
public:
	UDevice();
	UDevice(uint32_t mDeviceID, char mDeviceName[DEVICE_NAME_LENGHT]);
	~UDevice();
	uint8_t AddScenery(UScenery *mScenery);
	void DelScenery(uint32_t mSceneryID);
	uint32_t DoScenery();

	uint32_t DeviceID;
	char DeviceName[SCENERY_NAME_LENGHT];
	UScenery *SceneryList[MAX_SCENERY_NUMBER];
	uint32_t SceneryListIndex;
};

#endif // UDEVICE_H_


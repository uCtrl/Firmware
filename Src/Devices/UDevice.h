#ifndef UDEVICE_H_
#define UDEVICE_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"
#include "UScenery.h"

class UDevice
{
public:
	UDevice();
	UDevice(int mDeviceID, char mDeviceName[DEVICE_NAME_LENGHT]);
	~UDevice();
	bool AddScenery(UScenery *mScenery);
	void DelScenery(int mSceneryID);
	int DoScenery();

	int DeviceID;
	char DeviceName[SCENERY_NAME_LENGHT];
	UScenery *SceneryList[MAX_SCENERY_NUMBER];
	int SceneryListIndex;
};

#endif // UDEVICE_H_


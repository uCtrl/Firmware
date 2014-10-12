#ifndef UDEVICE_H_
#define UDEVICE_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"
#include "UScenario.h"

class UDevice
{
public:
	UDevice();
	UDevice(int mDeviceID, char mDeviceName[DEVICE_NAME_LENGHT]);
	~UDevice();
	bool AddScenario(UScenario *mScenario);
	void DelScenario(int mScenarioID);
	int DoScenario();

	int DeviceID;
	char DeviceName[SCENARIO_NAME_LENGHT];
	UScenario *ScenarioList[MAX_SCENARIO_NUMBER];
	int ScenarioListIndex;
};

#endif // UDEVICE_H_


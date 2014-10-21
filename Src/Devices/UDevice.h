#ifndef UDEVICE_H_
#define UDEVICE_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"
#include "UScenario.h"
#include "UDeviceType.h"

class UDevice
{
public:
	UDevice();
	UDevice(int mDeviceID, char* mDeviceName/*[DEVICE_NAME_LENGHT]*/, UDeviceType type);
	~UDevice();
	bool AddScenario(UScenario *mScenario);
	void DelScenario(int mScenarioID);
	int DoScenario();
	char* GetJSON();

	int m_deviceID;
	int m_pinNumber;
	int m_timeBetweenReads;

	int DeviceID;
	UDeviceType DeviceType;
	char* DeviceName/*[DEVICE_NAME_LENGHT]*/;
	UScenario *ScenarioList[MAX_DEVICE_NUMBER];
	int ScenarioCount;
};

#endif // UDEVICE_H_


#ifndef UDEVICE_H_
#define UDEVICE_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"
#include "UScenario.h"
#include "UDeviceType.h"

class UScenario;

class UDevice
{
public:
	UDevice();
	UDevice(int mDeviceID, char* mDeviceName, UDeviceType type);
	~UDevice();
	bool AddScenario(UScenario *mScenario);
	void DelScenario(int mScenarioID);
	int DoScenario();
	char* GetJSON();

	int m_pinNumber;
	int m_timeBetweenReads;

	int DeviceID;
	UDeviceType DeviceType;
	char* DeviceName;
	UScenario *ScenarioList[MAX_DEVICE_NUMBER];
	int ScenarioCount;
};

#endif // UDEVICE_H_


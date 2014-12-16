#ifndef UDEVICE_H_
#define UDEVICE_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"
#include "UScenario.h"
#include "UDeviceType.h"
#include <string>

class UScenario;

class UDevice
{
public:
	UDevice();
	UDevice(int mDeviceID, string mDeviceName, UDeviceType type, string description, string maxValue, string minValue, string value,
			int precision, int status, string unitLabel, bool enabled, int lastUpdated);
			
	~UDevice();
	bool AddScenario(UScenario *mScenario);
	void DelScenario(int mScenarioID);
	int DoScenario(int device);
	void GetJSON(char* returnJson);

	int DeviceID;
	UDeviceType DeviceType;
	string DeviceName;
	UScenario** ScenarioList;
	int ScenarioCount;
	double CurrentValue;
	
	int m_pinNumber;
	int m_timeBetweenReads;
	
	string Description;
	string MaxValue;
	string MinValue;
	string Value;
	int Precision;
	int Status;
	string UnitLabel;
	bool Enabled;
	int LastUpdated;
};

#endif // UDEVICE_H_



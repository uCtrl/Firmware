/*
 * UTaskHandler.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UTASKHANDLER_H_
#define UTASKHANDLER_H_

#include "rtos.h"
#include "UTaskCfgType.h"
#include "UTaskCfg.h"
#include "UConditionCfg.h"
#include "UTaskCfgType.h"
#include "UTaskRequest.h"
#include "UEvent.h"
#include "UDevice.h"
#include "UScenario.h"
#include "UTask.h"
#include "UCondition.h"
#include "TaskHandlerConfigFile.h"
#include "UTaskRequest.h"

#include "USensorHandler.h"
#include "UActuatorHandler.h"

extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

extern UTaskEvent EventPool[];
extern int EventPoolIndex;

// Forward Declaration
class USensorHandler;
class UActuatorHandler;

/** UTaskCfg class contains all user defined Scenery, Tasks, Conditions and
 *  Actions*/
class UTaskHandler
{
public:
	/** start the content of thread */
	UTaskHandler();
	UTaskHandler(USensorHandler* sensorHandler, UActuatorHandler* actuatorHandler);
	~UTaskHandler();
	void start();
private:
	/** handle UTaskRequest of UTaskRequestType EVENT */
	void handleTaskEvent(const UTaskEvent taskEvent);
	/** handle UTaskRequest of UTaskRequestType CONFIG */
	void handleTaskCfg(const UTaskCfg taskCfg);

	int AddDevice(UDevice *mDevice);
	void DelDevice(int mDeviceID);
	int AddEvent(UTaskEvent mEvent);
	void DelEvent(int mSensorID);
	int CheckDevice();

	UDevice* DeviceList[MAX_DEVICE_NUMBER];
	int DeviceListIndex;
	USensorHandler* m_sensorHandler;
	UActuatorHandler* m_actuatorHandler;
};

#endif /* UTASKHANDLER_H_ */

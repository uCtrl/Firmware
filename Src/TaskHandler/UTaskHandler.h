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
#include "UScenery.h"
#include "UTask.h"
#include "UCondition.h"
#include "TaskHandlerConfigFile.h"
#include "UTaskRequest.h"

extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

extern UTaskEvent EventPool[];
extern uint32_t EventPoolIndex;

/** UTaskCfg class contains all user defined Scenery, Tasks, Conditions and
 *  Actions*/
class UTaskHandler
{
public:
	/** start the content of thread */
	UTaskHandler();
	~UTaskHandler();
	void start();
private:
	/** handle UTaskRequest of UTaskRequestType EVENT */
	void handleTaskEvent(const UTaskEvent taskEvent);
	/** handle UTaskRequest of UTaskRequestType CONFIG */
	void handleTaskCfg(const UTaskCfg taskCfg);

	uint8_t AddDevice(UDevice *mDevice);
	void DelDevice(uint32_t mDeviceID);
	uint8_t AddEvent(UTaskEvent mEvent);
	void DelEvent(uint32_t mSensorID);
	uint32_t CheckDevice();

	UDevice* DeviceList[MAX_DEVICE_NUMBER];
	uint32_t DeviceListIndex;
};

#endif /* UTASKHANDLER_H_ */

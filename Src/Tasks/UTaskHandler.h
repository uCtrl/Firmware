/*
 * UTaskHandler.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UTASKHANDLER_H_
#define UTASKHANDLER_H_

#include "rtos.h"
#include "mbed.h"
#include "UTaskCfgType.h"
#include "UTaskCfg.h"
#include "UConditionCfg.h"
#include "UTaskCfgType.h"
#include "UTaskRequest.h"
#include "UEvent.h"
#include "TaskHandlerConfigFile.h"
#include "UTaskRequest.h"
#include "UMsgHandler.h"
#include "UDeviceType.h"

#include "UPlatform.h"
#include "UDevice.h"
#include "UScenario.h"
#include "UTask.h"
#include "UCondition.h"

#include "USensorHandler.h"
#include "UActuatorHandler.h"

extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;
extern Mail<UMsgHandlerMailType, 2> comDriverOutMail;

extern UTaskEvent EventPool[];
extern int EventPoolIndex;

// Forward Declaration
class USensorHandler;
class UActuatorHandler;
class UMsgHandler;

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

	/** handle UTaskRequest of UTaskRequestType GET_INFO */
	void handleGetInfo(const UTaskCfg taskCfg);

	/** handle UTaskRequest of UTaskRequestType SAVE_INFO */
	void handleSaveInfo(const UTaskCfg taskCfg);

	int AddDevice(UDevice *mDevice);
	void DelDevice(int mDeviceID);
	int AddEvent(UTaskEvent mEvent);
	void DelEvent(int mSensorID);
	int CheckDevice();

	void SendMessage(char* message, Endpoint* endpoint);

	void AddScenario(int scenarioId, int parentId, char* scenarioName);
	void AddTask(int taskId, int parentId, char* status);
	void AddCondition(int taskId, int parentId, int type);

	UPlatform* m_platform;
	UDevice* DeviceList[MAX_DEVICE_NUMBER];
	int DeviceListIndex;
	USensorHandler* m_sensorHandler;
	UActuatorHandler* m_actuatorHandler;
};

#endif /* UTASKHANDLER_H_ */

/*
 * UTaskHandler.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UTASKHANDLER_H_
#define UTASKHANDLER_H_

#include "cfg.h"
#include "rtos.h"
#include "mbed.h"
#include "UTaskCfgType.h"
#include "UTaskCfg.h"
#include "UConditionCfg.h"
#include "UTaskEvent.h"
#include "TaskHandlerConfigFile.h"
#include "UMsgHandler.h"
#include "UDeviceType.h"

#include "UPlatform.h"
#include "UDevice.h"
#include "UScenario.h"
#include "UTask.h"
#include "UCondition.h"

#include "UDeviceHandler.h"
#include "UTaskRequest.h"

//class UTaskRequest;
//struct UTaskCfg;

//extern Semaphore semMailUTaskHandler;
//extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER> mailUTaskHandler;
//extern Mail<UMsgHandlerMailType, 2> comDriverOutMail;

extern UTaskEvent EventPool[];
extern int EventPoolIndex;

// Forward Declaration
class UMsgHandler;
class UDeviceHandler;

/** UTaskCfg class contains all user defined Scenery, Tasks, Conditions and
 *  Actions*/
class UTaskHandler
{
public:
	/** start the content of thread */
	UTaskHandler();
	UTaskHandler(UDeviceHandler* a_deviceHandler);
	~UTaskHandler();
	void start();
	UPlatform* m_platform;
	
private:
	/** handle UTaskRequest of UTaskRequestType EVENT */
	void handleTaskEvent(const UTaskEvent taskEvent);
	
	/** handle UTaskRequest of UTaskRequestType DELETE */
	void handleDelete(const UTaskCfg taskCfg);

	/** handle UTaskRequest of UTaskRequestType GET_INFO */
	void handleGetInfo(const UTaskCfg taskCfg);

	/** handle UTaskRequest of UTaskRequestType SAVE_INFO */
	void handleSaveInfo(const UTaskCfg taskCfg);

	UDevice* DeviceList[MAX_DEVICE_NUMBER];
	int DeviceListIndex;
	UDeviceHandler* m_deviceHandler;
};

#endif /* UTASKHANDLER_H_ */


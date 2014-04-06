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
#include "UActionCfg.h"
#include "UTaskCfgType.h"
#include "UTaskRequest.h"
#define MAIL_LEN_UTASKHANDLER 8
extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

/** UTaskCfg class contains all user defined Scenery, Tasks, Conditions and
 *  Actions*/
class UTaskHandler
{
public:
	/** start the content of thread */
	void start();
private:
	/** handle UTaskRequest of UTaskRequestType EVENT */
	void handleTaskEvent(const UTaskEvent taskEvent);
	/** handle UTaskRequest of UTaskRequestType CONFIG */
	void handleTaskCfg(const UTaskCfg taskCfg);
};

#endif /* UTASKHANDLER_H_ */

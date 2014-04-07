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
#include "UScenery.h"
#include "UTask.h"
#include "UCondition.h"
#include "UAction.h"
#include "TaskHandlerConfigFile.h"

extern Semaphore semMailUTaskHandler;
extern Mail<UTaskCfg, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

/** UTaskCfg class contains all user defined Scenery, Tasks, Conditions and
 *  Actions*/
class UTaskHandler
{
public:
	UScenery *MainScenery;
	/** start the content of thread */
	void start();
};

#endif /* UTASKHANDLER_H_ */

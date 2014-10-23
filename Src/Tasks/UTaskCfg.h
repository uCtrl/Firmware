/*
 * UTaskCfg.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UTASKCFG_H_
#define UTASKCFG_H_

#include "UConditionCfg.h"
#include "UTaskCfgMod.h"
#include "EthernetInterface.h"
#include "UTaskCfgType.h"

#include "UPlatform.h"
#include "UDevice.h"
//#include "UScenario.h"
//#include "UTask.h"
//#include "UCondition.h"

class UScenario;
class UTask;
class UCondition;

/** UTaskCfg struct contains all data for the creation of sceneries, tasks,
 * actions and conditions in the task system.
 * If the UTaskCfgType is UScenery, parentId is NULL.
 * If UTaskCfgType is UScenery or UTask, conditionCfg and actionCfg are NULL.
 * If UTaskCfgType is UCondition, use conditionCfg.
 * If UTaskCfgType is UAction, use actionCfg.*/

typedef struct
{
	UTaskCfgType taskCfgType;
	UTaskCfgMod taskCfgMod;
	int id;
	int parentId;
	Endpoint* endpoint;
	union
	{
		UConditionCfg conditionCfg;
		int ActionValue;
	};

	UPlatform* platform;
	UDevice* device;
	UScenario* scenario;
	UTask* task;
	UCondition* condition;
} UTaskCfg;

#endif /* UTASKCFG_H_ */

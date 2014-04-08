/*
 * UTaskCfg.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UTASKCFG_H_
#define UTASKCFG_H_

#include "UTaskCfgType.h"
#include "UConditionCfg.h"
#include "UActionCfg.h"

/** UTaskCfg struct contains all data for the creation of sceneries, tasks,
 * actions and conditions in the task system.
 * If the UTaskCfgType is UScenery, parentId is NULL.
 * If UTaskCfgType is UScenery or UTask, conditionCfg and actionCfg are NULL.
 * If UTaskCfgType is UCondition, use conditionCfg.
 * If UTaskCfgType is UAction, use actionCfg.*/
typedef struct
{
	UTaskCfgType taskCfgType;
	uint32_t id;
	uint32_t parentId;
	union
	{
		UConditionCfg conditionCfg;
		UActionCfg actionCfg;
	};
} UTaskCfg;



#endif /* UTASKCFG_H_ */

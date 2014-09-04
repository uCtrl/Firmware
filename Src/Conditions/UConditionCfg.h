/*
 * ConditionCfg.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UCONDITIONCFG_H_
#define UCONDITIONCFG_H_

#include "UOperatorType.h"

/** UConditionCfg struct contains additional data to complement UTaskCfg. It
 *  contains all data useful to the creation of a condition in the task
 *  system.*/
typedef struct
{
	UOperatorType operatorType;
	int value;
	int sensorId;
} UConditionCfg;

#endif /* UCONDITIONCFG_H_ */

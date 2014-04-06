/*
 * UTaskCfgMod.h
 *
 *  Created on: Apr 6, 2014
 *      Author: uctrl
 */

#ifndef UTASKCFGMOD_H_
#define UTASKCFGMOD_H_

/** UTaskCfgMod enum is used to distinct type of modification to apply to the
 * configuration in the task system*/
typedef enum
{
	TASK_CFG_MOD_NONE = 0,
	TASK_CFG_ADD = 1,
	TASK_CFG_EDIT = 2,
	TASK_CFG_DELETE = 3,
} UTaskCfgMod;



#endif /* UTASKCFGMOD_H_ */

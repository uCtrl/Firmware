/*
 * UTaskCfgTypeElementType.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UTASKCFGTYPETYPE_H_
#define UTASKCFGTYPETYPE_H_

/** UTaskCfgType enum is used to distinct type of configuration
 *  in the task system*/
typedef enum
{
	TASK_CFG_TYPE_NONE = 0,
	USCENERY = 1,
	UTASK = 2,
	UCONDITION = 3,
	UACTION = 4
} UTaskCfgType;

#endif /* UTASKCFGTYPETYPE_H_ */

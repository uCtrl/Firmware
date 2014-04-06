/*
 * UActionCfg.h
 *
 *  Created on: Apr 1, 2014
 *      Author: uctrl
 */

#ifndef UACTIONCFG_H_
#define UACTIONCFG_H_

/** UActionCfg struct contains additional data to complement UTaskCfg. It
 *  contains all data useful to the creation of an action in the task
 *  system.*/
typedef struct
{
	uint32_t value;
	uint32_t actuatorId;
} UActionCfg;



#endif /* UACTIONCFG_H_ */

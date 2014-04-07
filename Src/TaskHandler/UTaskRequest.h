/*
 * UTaskRequest.h
 *
 *  Created on: Apr 4, 2014
 *      Author: uctrl
 */

#ifndef UTASKREQUEST_H_
#define UTASKREQUEST_H_

#include "UTaskCfg.h"
#include "UTaskRequestType.h"
#include "UEvent.h"
#include "UTaskRequest.h"

typedef struct
{
	UTaskRequestType uTaskRequestType;
	union
	{
		UTaskCfg taskCfg;
		UTaskEvent event;
	};
} UTaskRequest;



#endif /* UTASKREQUEST_H_ */

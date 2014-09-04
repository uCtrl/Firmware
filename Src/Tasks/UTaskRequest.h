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

typedef struct
{
	UTaskRequestType taskRequestType;
	union
	{
		UTaskCfg taskCfg;
		UTaskEvent event;
	};
} UTaskRequest;


#endif /* UTASKREQUEST_H_ */

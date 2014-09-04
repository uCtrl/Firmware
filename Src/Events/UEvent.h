/*
 * UEvent.h
 *
 *  Created on: Apr 4, 2014
 *      Author: uctrl
 */

#ifndef UEVENT_H_
#define UEVENT_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"

typedef struct
{
	int sensorId;
	int value;
} UTaskEvent;

#endif /* UEVENT_H_ */

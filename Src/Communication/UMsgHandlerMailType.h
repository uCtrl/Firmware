/*
* UMsgHandlerMailType.h
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#ifndef UMSGHANDLERMAILTYPE_H_
#define UMSGHANDLERMAILTYPE_H_

#include "cfg.h"
#include "EthernetInterface.h"

typedef struct {
	Endpoint endPoint;
	char msg[COM_BUFFER_SIZE];
} UMsgHandlerMailType;

#endif  // UMSGHANDLERMAILTYPE_H_

/*
 * UJsonUtils.h
 *
 *  Created on: Oct 20, 2014
 *      Author: uctrl
 */

#include "mbed.h"
#include "cfg.h"
#include "UTaskCfgType.h"

#ifndef UJSONUTILS_H_
#define UJSONUTILS_H_

class UJsonUtils {
public:

	static void substr(char* arr, char* returnArr, int begin, int len);
	static void substr(const char* arr, char* returnArr, int begin, int len);

	static void AddJsonGetShell(char* JSON, int parent, bool status, int error, int messageType, int size, UTaskCfgType taskCfgType, int messageId);
	static char* AddJsonSaveShell(int messageType, bool status, int error);
	static bool ConvertToBool(const char* str);
	
	static void SetIpAddress(char* ip);
	static char* GetIpAddress();

	static char* m_IpAddress;
};

#endif /* UJSONUTILS_H_ */


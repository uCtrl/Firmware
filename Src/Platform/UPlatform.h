/*
 * UPlatform.h
 *
 *  Created on: Oct 17, 2014
 *      Author: uctrl
 */

#include "mbed.h"
#include <string>

#ifndef UPLATFORM_H_
#define UPLATFORM_H_


class UPlatform {
public:
	UPlatform();
	UPlatform(int id, string firmwareVersion, string name, string ip, int port, int status, string room, bool enabled, int lastUpdated);
	virtual ~UPlatform();

	void GetJSON(char* returnValue);

	int Id;
	string FirmwareVersion;
	string Name;
	string Ip;
	int Port;
	int Status;
	string Room;
	bool Enabled;
	int LastUpdated;
};

#endif /* UPLATFORM_H_ */


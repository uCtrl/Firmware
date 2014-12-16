/*
 * UPlatform.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: uctrl
 */

#include <Platform/UPlatform.h>

extern Serial usbSerial;

UPlatform::UPlatform()
{
	Id = -1;
	FirmwareVersion = "None";
	Name = "Undefined";
	Ip = "";
	Port = 0;
	Status = 0;
	Room = "Undefined";
	Enabled = false;
	LastUpdated = -1;
}

UPlatform::UPlatform(int id, string firmwareVersion, string name, string ip, int port, int status, string room, bool enabled, int lastUpdated) 
{
	Id = id;
	FirmwareVersion = firmwareVersion;
	Name = name;
	Ip = ip;
	Port = port;
	Status = status;
	Room = room;
	Enabled = enabled;
	LastUpdated = lastUpdated;
}

UPlatform::~UPlatform() 
{
}

void UPlatform::GetJSON(char* returnValue)
{
	strcpy(returnValue, "{\"id\":\"");
	char buf1[10];
	sprintf(buf1, "%d", Id);
	strcat(returnValue, buf1);

	strcat(returnValue, "\", \"firmwareVersion\":\"");
	strcat(returnValue, FirmwareVersion.c_str());
	
	strcat(returnValue, "\", \"name\":\"");
	strcat(returnValue, Name.c_str());
	
	strcat(returnValue, "\", \"ip\":\"");
	strcat(returnValue, Ip.c_str());
	
	strcat(returnValue, "\", \"port\":");
	char buf2[10];
	sprintf(buf2, "%d", Port);
	strcat(returnValue, buf2);
	
	strcat(returnValue, ", \"status\":");
	char buf3[10];
	sprintf(buf3, "%d", Status);
	strcat(returnValue, buf3);
	
	strcat(returnValue, ", \"room\":\"");
	strcat(returnValue, Room.c_str());
	
	strcat(returnValue, "\", \"enabled\":");
	if(Enabled)
		strcat(returnValue, "true");
	else
		strcat(returnValue, "false");
	
	strcat(returnValue, ", \"lastUpdated\":");
	char buf4[10];
	sprintf(buf4, "%d", LastUpdated);
	strcat(returnValue, buf4);
	
	strcat(returnValue, "}\0");
}


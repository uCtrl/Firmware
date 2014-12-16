#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "PathConfirm.h"
#include "HostMessage.h"
#include "WordArray.h"

PathConfirm::PathConfirm(void)
{
	InitializeData();
}

PathConfirm::PathConfirm(BYTE * data, int offset)
{
	memset(_PathConfirm._ShortAddressArray, 0, sizeof(_PathConfirm._ShortAddressArray));
	int msgLength=0;
	//
	// Get the message length;
	//
	memcpy(&msgLength, &data[offset+2], 2);
	msgLength += 4; // add the id, origin and length bytes.
	ReadGenericMessage(&_PathConfirm, msgLength, data, offset);
}
PathConfirm::PathConfirm(const PathConfirm & msg)
{
	memcpy(&_PathConfirm, & msg._PathConfirm, sizeof(PathDiscoverConfirm));
}

PathConfirm::~PathConfirm(void)
{
}

void PathConfirm::InitializeData()
{
	memset(&_PathConfirm, 0, sizeof(PathDiscoverConfirm));
	_PathConfirm._Header._Id = Discover_Id;
	_PathConfirm._Header._Origin = 0;
}

HostMessage * PathConfirm::CreateMessage(BYTE * data, int offset)
{
	return new PathConfirm(data, offset);
}

void PathConfirm::CopyTo(HostMessage * msg)
{
	PathConfirm * temp = (PathConfirm *) msg;
	memcpy(&temp->_PathConfirm, &_PathConfirm, sizeof(PathDiscoverConfirm));
}

int PathConfirm::GetMsgSize()
{
	int msgLength = 0;
	msgLength += 4; // id, origin, msglength..
	msgLength += 4; // crc's
	msgLength += 2; //status;
	msgLength += 2; // short address
	msgLength += 2; // count of devices
	msgLength += GetNumberOfDevices() * 2; // length of path.
	return msgLength;
}

int PathConfirm::ReadMessage(BYTE * data, int offset)
{
	memset(_PathConfirm._ShortAddressArray, 0, sizeof(_PathConfirm._ShortAddressArray)*2);
	int msgLength=0;
	memcpy(&msgLength, &data[offset+2], 2);
	msgLength += 4; // add the id, origin and length bytes.
	return ReadGenericMessage(&_PathConfirm, msgLength, data, offset);
}


TextString PathConfirm::ToString()
{
	TextString temp;
	temp.Format("Path Discover Confirm: Id= %d\r\n", GetId());
	temp.AppendFormat("   Status:            0x%4.4X\r\n", GetStatus());
	temp.AppendFormat("   Short Address:     0x%4.4X\r\n", GetShortAddress());  
	temp.AppendFormat("   Number of Devices: %d\r\n", GetNumberOfDevices());  
	if (GetNumberOfDevices() > 0)
	{
		WordArray pathArray(GetNumberOfDevices(), GetPath());
		temp.AppendFormat("   Path:              %s\r\n", (char *) pathArray.ToString());
	}
	temp.AppendFormat("\r\n");
	return temp;
}

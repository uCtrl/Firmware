#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Network_Start.h"
#include "MessageIds.h"

Network_Start_Request::Network_Start_Request(void)
{
	InitializeData();
}

Network_Start_Request::Network_Start_Request(BYTE * msg, int offset)
{
	ReadGenericMessage(&_NetworkStartRequest, sizeof(_NetworkStartRequest), msg, offset);
}
Network_Start_Request::Network_Start_Request(const Network_Start_Request & msg)
{
	memcpy(&_NetworkStartRequest, &msg._NetworkStartRequest, sizeof(NetworkStartRequest));
}

Network_Start_Request::~Network_Start_Request(void)
{
}

HostMessage * Network_Start_Request::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Network_Start_Request(data, offset);
	return msg;
}

TextString Network_Start_Request::ToString()
{
	TextString temp;
	temp.Format("Network_Start Request: Id=   %d  -  PAN Id: 0x%4.4X\r\n\r\n", GetId(), _NetworkStartRequest._PAN_Id);
	return temp;
}

void Network_Start_Request::InitializeData()
{
	memset(&_NetworkStartRequest, 0, sizeof(_NetworkStartRequest));
	_NetworkStartRequest._Header._Id = Network_Start_Id;
	_NetworkStartRequest._Header._Origin = 0x80;
};

/*


Network Confirm


*/
Network_Start_Confirm::Network_Start_Confirm(void)
{
	InitializeData();
}

Network_Start_Confirm::Network_Start_Confirm(BYTE * msg, int offset)
{
	ReadGenericMessage(&_NetworkStartConfirm, sizeof(NetworkStartConfirm), msg, offset);
}
Network_Start_Confirm::Network_Start_Confirm(const Network_Start_Confirm & msg)
{
	memcpy(&_NetworkStartConfirm, &msg._NetworkStartConfirm, sizeof(NetworkStartConfirm));
}

Network_Start_Confirm::~Network_Start_Confirm(void)
{
}

HostMessage * Network_Start_Confirm::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Network_Start_Confirm(data, offset);
	return msg;
}

TextString Network_Start_Confirm::ToString()
{
	TextString temp;
	temp.Format("Network_Start Confirm: Id=   %d  -  Status: 0x%4.4X\r\n\r\n", GetId(), _NetworkStartConfirm._Status);
	return temp;
}

void Network_Start_Confirm::InitializeData()
{
	memset(&_NetworkStartConfirm, 0, sizeof(_NetworkStartConfirm));
	_NetworkStartConfirm._Header._Id = Network_Start_Id;
	_NetworkStartConfirm._Header._Origin = 0x00;
};

#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Detach.h"
#include "MessageIds.h"
#include "ByteArray.h"

Detach_Request::Detach_Request(void)
{
	InitializeData();
}

Detach_Request::Detach_Request(BYTE * msg, int offset)
{
	ReadGenericMessage(&_DetachRequest, sizeof(DetachRequest), msg, offset);
}

Detach_Request::Detach_Request(const Detach_Request & msg) : HostMessage(msg)
{
	memcpy(&_DetachRequest, & msg._DetachRequest, sizeof(DetachRequest));
}

Detach_Request::~Detach_Request(void)
{
}

void Detach_Request::InitializeData()
{
	memset(&_DetachRequest, 0, sizeof(DetachRequest));
	_DetachRequest._Header._Id = Detach_Id;
	_DetachRequest._Header._Origin = 0x80;
}


HostMessage * Detach_Request::CreateMessage(BYTE * data, int offset)
{
	return new Detach_Request(data, offset);
}
TextString Detach_Request::ToString()
{
	TextString temp;
	temp.Format("Detach Request: Id=   %d\r\n", GetId());
	ByteArray ba(sizeof(_DetachRequest._ExtendedAddress), _DetachRequest._ExtendedAddress);
	temp.AppendFormat("   Extended Address: 0x%s\r\n\r\n", (char *)ba.ToString("%2.2X"));
	return temp;
}

void Detach_Request::Set_ExtendedAddress( BYTE * address)
{
	if (address == NULL)
	{
		memset(_DetachRequest._ExtendedAddress, 0, sizeof(_DetachRequest._ExtendedAddress));
	}
	else
	{
		memcpy(_DetachRequest._ExtendedAddress, address, sizeof(_DetachRequest._ExtendedAddress));
	}
}

/*

Detach Confirm Message


*/
Detach_Confirm::Detach_Confirm(void)
{
	InitializeData();
}

Detach_Confirm::Detach_Confirm(BYTE * msg, int offset)
{
	ReadGenericMessage(&_DetachConfirm, sizeof (DetachConfirm), msg, offset);
}

Detach_Confirm::Detach_Confirm(const Detach_Confirm & dc)
{
	memcpy(&_DetachConfirm, & dc._DetachConfirm, sizeof(DetachConfirm));
}

Detach_Confirm::~Detach_Confirm(void)
{
}
void Detach_Confirm::InitializeData()
{
	memset(&_DetachConfirm, 0, sizeof(DetachConfirm));
	_DetachConfirm._Header._Id = Detach_Id;
	_DetachConfirm._Header._Origin = 0x00;
}

HostMessage * Detach_Confirm::CreateMessage(BYTE * data, int offset)
{
	MessageHeader mh(data, offset);
	HostMessage * msg = NULL;
	if (mh.GetMessageLength() == 10 + 4)
	{
		msg = new Detach_Confirm(data, offset);
	}
	else if (mh.GetMessageLength() == 8 + 4)
	{
		msg = new Detach_Indication(data, offset);
	}
	return msg;
}

TextString Detach_Confirm::ToString()
{
	TextString temp;
	temp.Format("Detach Confirm: Id=   %d\r\n", GetId());
	temp.AppendFormat("   Status:           %d\r\n", _DetachConfirm._Status);
	ByteArray ba(sizeof(_DetachConfirm._ExtendedAddress), _DetachConfirm._ExtendedAddress);
	temp.AppendFormat("   Extended Address: 0x%s\r\n\r\n", (char* )ba.ToString("%2.2X"));
	return temp;
}

void Detach_Confirm::Set_ExtendedAddress( BYTE * address)
{
	memcpy(_DetachConfirm._ExtendedAddress, address, sizeof(_DetachConfirm._ExtendedAddress));
}
/*


Detach Indication Message


*/
Detach_Indication::Detach_Indication(void)
{
	InitializeData();
}

Detach_Indication::Detach_Indication(BYTE * msg, int offset)
{
	ReadGenericMessage(&_DetachIndication, sizeof(DetachIndication), msg, offset);
}

Detach_Indication::Detach_Indication(const Detach_Indication & msg)
{
	memcpy(&_DetachIndication, & msg._DetachIndication, sizeof(DetachIndication));
}

Detach_Indication::~Detach_Indication(void)
{

}

void Detach_Indication::InitializeData()
{
	memset(&_DetachIndication, 0, sizeof(DetachIndication));
	_DetachIndication._Header._Id = Detach_Id;
	_DetachIndication._Header._Origin = 0x00;
}

HostMessage * Detach_Indication::CreateMessage(BYTE * data, int offset)
{
	MessageHeader mh(data, offset);
	HostMessage * msg = NULL;
	if (mh.GetMessageLength() == 10 + 4)
	{
		msg = new Detach_Confirm(data, offset);
	}
	else if (mh.GetMessageLength() == 8 + 4)
	{
		msg = new Detach_Indication(data, offset);
	}
	return msg;
}

TextString Detach_Indication::ToString()
{
	TextString temp;
	temp.Format("Detach Indication: Id=   %d\r\n", GetId());
	ByteArray ba(sizeof(_DetachIndication._ExtendedAddress), _DetachIndication._ExtendedAddress);
	temp.AppendFormat("   Extended Address: 0x%s\r\n\r\n", (char *) ba.ToString("%2.2X"));
	return temp;
}

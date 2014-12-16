#include "Log.h"
#include "Attach.h"
#include "MessageIds.h"
#include "ByteArray.h"
#include "WordArray.h"
#include "TLV_Messages.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"


Attach_Request::Attach_Request(void)
{
	InitializeData();
}

Attach_Request::Attach_Request(BYTE * msg, int offset)
{
	ReadGenericMessage(&_AttachRequest, sizeof(AttachRequest), msg, offset);
}

Attach_Request::Attach_Request(const Attach_Request & msg) : HostMessage(msg)
{
	memcpy(&_AttachRequest, & msg._AttachRequest, sizeof(AttachRequest));
}

Attach_Request::~Attach_Request(void)
{

}

void Attach_Request::InitializeData()
{
	memset(&_AttachRequest, 0, sizeof(AttachRequest));
	_AttachRequest._Header._Id = Attach_Id;
	_AttachRequest._Header._Origin = 0x80;
}

HostMessage * Attach_Request::CreateMessage(BYTE * data, int offset)
{
	return new Attach_Request(data, offset);
}

TextString Attach_Request::ToString()
{
	TextString temp;
	temp.Format("Attach Request: Id=   %d\r\n", GetId());
	temp.AppendFormat("   PAN Id:                      0x%4.4X\r\n", _AttachRequest._PAN_Id);
	temp.AppendFormat("   LBA Address (short address): 0x%4.4X\r\n\r\n", _AttachRequest._LBA_Address);
	return temp;
}
/*

Attach Confirm message


*/

Attach_Confirm::Attach_Confirm(void)
{
	InitializeData();
}

Attach_Confirm::Attach_Confirm(BYTE * msg, int offset)
{
	ReadGenericMessage(&_AttachConfirm, sizeof(AttachConfirm), msg, offset);
}

Attach_Confirm::Attach_Confirm(const Attach_Confirm & msg) : HostMessage(msg)
{
	memcpy(&_AttachConfirm, & msg._AttachConfirm, sizeof(AttachConfirm));
}

Attach_Confirm::~Attach_Confirm(void)
{
}

void Attach_Confirm::InitializeData()
{
	memset(&_AttachConfirm, 0, sizeof(AttachConfirm));
	_AttachConfirm._Header._Id = Attach_Id;
	_AttachConfirm._Header._Origin = 0x00;
}

HostMessage * Attach_Confirm::CreateMessage(BYTE * data, int offset)
{
	MessageHeader mh(data, offset);
	HostMessage * msg = NULL;
	if (mh.GetMessageLength() == 10) 
	{
		msg = new Attach_Confirm(data, offset);
	}
	else if (mh.GetMessageLength() == 30)
	{
		msg = new Attach_Indication(data, offset);
	}
	else
	{
		Log::Write("Invalid msg: Id= %d, Len= %d\r\n", mh.GetId(), mh.GetMessageLength());
	}
	return msg;
}
TextString Attach_Confirm::ToString()
{
	TextString temp;
	temp.Format("Attach Confirm: Id=   %d\r\n", GetId());
	temp.AppendFormat("   Status:          0x%4.4X\r\n", _AttachConfirm._Status);
	temp.AppendFormat("   Network Address: 0x%4.4X\r\n", _AttachConfirm._NetworkAddress);
	temp.AppendFormat("   PAN Id:          0x%4.4X\r\n\r\n", _AttachConfirm._PAN_Id);
	return temp;
}

/*


Attach Indication Message


*/

Attach_Indication::Attach_Indication(void)
{
	InitializeData();
}

Attach_Indication::Attach_Indication(BYTE * msg, int offset)
{
	ReadMessage(msg, offset);
}
Attach_Indication::Attach_Indication(const Attach_Indication & msg) : HostMessage(msg)
{
	memcpy(&_AttachIndication, & msg._AttachIndication, sizeof(AttachIndication));
}

Attach_Indication::~Attach_Indication(void)
{
}
int Attach_Indication::ReadMessage(BYTE * msg, int offset)
{
	offset = ReadGenericMessage(&_AttachIndication, sizeof(AttachIndication), msg, offset);
	//
	// Swap everything but the last word
	//
	for(int index= 0; index < 16; index+= 2)
	{
		SwapInLine(&_AttachIndication._IPv6_Address[index], 2);
	}
	return offset;
}

void Attach_Indication::InitializeData()
{
	memset(&_AttachIndication, 0, sizeof(AttachIndication));
	_AttachIndication._Header._Id = Attach_Id;
	_AttachIndication._Header._Origin = 0x00;
}

HostMessage * Attach_Indication::CreateMessage(BYTE * data, int offset)
{
	MessageHeader mh(data, offset);
	HostMessage * msg = NULL;
	if (mh.GetMessageLength() == (4 + 6))  // CRC lengths and the data length
	{
		msg = new Attach_Confirm(data, offset);
	}
	else if (mh.GetMessageLength() == (4 + 26)) // CRC lengths and the data length
	{
		msg = new Attach_Indication(data, offset);
	}
	else
	{
		Log::Write("Invalid msg: Id= %d, Len= %d\r\n", mh.GetId(), mh.GetMessageLength());
	}
	return msg;
}
	
TextString Attach_Indication::ToString()
{
	TextString temp;
	temp.Format("Attach Indication: Id=   %d\r\n", GetId());
	ByteArray ipv6(sizeof(_AttachIndication._IPv6_Address), _AttachIndication._IPv6_Address);
	temp.AppendFormat("   IPv6 Address:     0x%s\r\n", (char *)ipv6.ToString("%2.2X"));

	ByteArray extended(sizeof(_AttachIndication._ExtendedAddress), _AttachIndication._ExtendedAddress);
	temp.AppendFormat("   Extended Address: 0x%s\r\n", (char *)extended.ToString("%2.2X"));
	temp.AppendFormat("   Capability Info:  %d\r\n\r\n", _AttachIndication._CapabilityInfo);
	
	return temp;
}

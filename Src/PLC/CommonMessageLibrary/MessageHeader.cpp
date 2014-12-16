#include "MessageHeader.h"
extern Serial usbSerial;
MessageHeader::MessageHeader(void)
{
	_Id = 0;
	_Origin = 0x80;  // Org = host, RPY = 0, Seq = 0
	_MessageLength = 0;
	_Offset = 0;
}
MessageHeader::MessageHeader(const MessageHeader & header)
{
	_Id = header._Id;
	_Origin = header._Origin;
	_MessageLength = header._MessageLength;
	_Offset = header._Offset;
}

MessageHeader::MessageHeader(BYTE * data, int offset)
{
	_Offset = (UINT16)offset;
	_Id = data[_Offset++];
	_Origin = data[_Offset++];
	_MessageLength = *((UINT16*)&data[_Offset]);
	_Offset += sizeof(_MessageLength);
}

MessageHeader & MessageHeader::operator = (const BYTE * data)
{
	if ( data != NULL)
	{
		_Offset = 0;
		_Id = data[_Offset++];
		_Origin = data[_Offset++];
		_MessageLength = *((UINT16*)&data[_Offset]);
		_Offset += sizeof(_MessageLength);
	}
	else
	{
		_Id = 0;
		_Origin = 0;
		_MessageLength = 0;
		_Offset = 0;
	}

	return *this;
}

Message * MessageHeader::MakeHeader()
{
	BYTE * data = new BYTE[HeaderLength()];
	_Offset = 0;
	data[_Offset++] = _Id;
	data[_Offset++] = _Origin;

	*((UINT16 *) & data[_Offset]) = _MessageLength;
	_Offset += sizeof(_MessageLength);

	return new Message(_Offset, data);
}

int MessageHeader::ReadHeader(BYTE * data, int offset)
{
	_Offset = (UINT16)offset;
	_Id = data[_Offset++];
	_Origin = data[_Offset++];
	_MessageLength = *((UINT16*)&data[_Offset]);
	_Offset += sizeof(_MessageLength);
	
	return _Offset;
}

MessageHeader::~MessageHeader(void)
{
}

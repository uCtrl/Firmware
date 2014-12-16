#include "TLV.h"


TLV::TLV(void)
{
	_Type = 0;
}

TLV::TLV(int length) : Message(length)
{
	_Type = 0;
}

TLV::TLV(int type, int length) : Message(length)
{
	_Type = (UINT16)type;
}

TLV::TLV(const TLV & tlv) : Message(tlv)
{
	_Type = tlv._Type;
}

TLV::~TLV(void)
{
}

int TLV::Read_TLV(BYTE * data, int offset)
{
	_Type = *((UINT16 *) &data[offset]);
	offset += 2;

	UINT16 length = *((UINT16 *) &data[offset]);
	offset += 2;

	offset = ReadMessage(length, data, offset);

	return offset;
}

Message * TLV::Write_TLV()
{
	Message * msg = new Message(_MessageSize + 4 /* type and length*/);
	
	int offset = 0;
	*((UINT16 *) & msg->_Message[offset]) = _Type;
	offset+= 2;
	*((UINT16 *) & msg->_Message[offset]) = (UINT16)_MessageSize;
	offset +=2;

	memcpy(&msg->_Message[offset], _Message, _MessageSize);
	offset += _MessageSize;

	return msg;
}
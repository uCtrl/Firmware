#include "HostMessages.h"
#include "UPlcConfigFile.h"
BYTE * MakeStatusMessage_1(struct StatusMessage * message, BYTE id, BYTE org, BYTE rpy, BYTE seq)
{
	UINT16 totalMessageLength = sizeof(struct StatusMessage);
	int payloadLength = totalMessageLength - sizeof(struct Header);
	BYTE * msg = (BYTE *) malloc(totalMessageLength);
	message->_Header._Id = id;
	message->_Header._Origin = 0;
	if (org != 0)
	{
		message->_Header._Origin |= 0x80;
	}
	if (rpy != 0)
	{
		message->_Header._Origin |= 0x40;
	}
	message->_Header._Origin |= (seq & 0x0F);
	message->_Header._Length = (UINT16)payloadLength;

	MakeCRC_Header(&message->_CRC_Header, &message->_Header, sizeof(struct Header), & message->_Status, sizeof(UINT16));

	memcpy(msg, message, totalMessageLength);
	return msg;
}
/*
int ReadStatusMessage(struct StatusMessage * statusMessage, BYTE * message, int offset)
{
	memcpy(statusMessage, &message[offset], sizeof(struct StatusMessage));
	offset += sizeof(struct StatusMessage);
	return offset;
}
*/
